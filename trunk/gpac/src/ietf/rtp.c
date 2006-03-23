/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005 
 *					All rights reserved
 *
 *  This file is part of GPAC / IETF RTP/RTSP/SDP sub-project
 *
 *  GPAC is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *   
 *  GPAC is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *   
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *
 */

#include <gpac/internal/ietf_dev.h>
#include <gpac/bitstream.h>

#define MAX_RTP_SN	0x10000


GF_RTPChannel *gf_rtp_new()
{
	GF_RTPChannel *tmp;
	tmp = malloc(sizeof(GF_RTPChannel));
	memset(tmp, 0, sizeof(GF_RTPChannel));
	tmp->first_SR = 1;
	tmp->SSRC = gf_rand();
	
	return tmp;
}

void gf_rtp_del(GF_RTPChannel *ch)
{
	if (!ch) return;
	if (ch->rtp) gf_sk_del(ch->rtp);
	if (ch->rtcp) gf_sk_del(ch->rtcp);
	if (ch->net_info.source) free(ch->net_info.source);
	if (ch->net_info.destination) free(ch->net_info.destination);
	if (ch->net_info.Profile) free(ch->net_info.Profile);
	if (ch->po) gf_rtp_reorderer_del(ch->po);
	if (ch->send_buffer) free(ch->send_buffer);

	if (ch->CName) free(ch->CName);
	if (ch->s_name) free(ch->s_name);
	if (ch->s_email) free(ch->s_email);
	if (ch->s_location) free(ch->s_location);
	if (ch->s_phone) free(ch->s_phone);
	if (ch->s_tool) free(ch->s_tool);
	if (ch->s_note) free(ch->s_note);
	if (ch->s_priv) free(ch->s_priv);
	free(ch);
}



GF_Err gf_rtp_setup_transport(GF_RTPChannel *ch, GF_RTSPTransport *trans_info, char *remote_address)
{
	if (!ch || !trans_info) return GF_BAD_PARAM;
	//assert we have at least ONE source ID
	if (!trans_info->source && !remote_address) return GF_BAD_PARAM;

	if (ch->net_info.destination) free(ch->net_info.destination);
	if (ch->net_info.Profile) free(ch->net_info.Profile);
	if (ch->net_info.source) free(ch->net_info.source);
	memcpy(&ch->net_info, trans_info, sizeof(GF_RTSPTransport));

	if (trans_info->destination) 
		ch->net_info.destination = strdup(trans_info->destination);

	if (trans_info->Profile) 
		ch->net_info.Profile = strdup(trans_info->Profile);

	if (trans_info->source) {
		ch->net_info.source = strdup(trans_info->source);
	} else if (!ch->net_info.IsUnicast && trans_info->destination) {
		ch->net_info.source = strdup(trans_info->destination);
	} else {
		ch->net_info.source = strdup(remote_address);
	}
	//check we REALLY have unicast or multicast
	if (gf_sk_is_multicast_address(ch->net_info.source) && ch->net_info.IsUnicast) return GF_SERVICE_ERROR;
	return GF_OK;
}


void gf_rtp_reset_buffers(GF_RTPChannel *ch)
{
	if (ch->rtp) gf_sk_reset(ch->rtp);
	if (ch->rtcp) gf_sk_reset(ch->rtcp);
	if (ch->po) gf_rtp_reorderer_reset(ch->po);
	/*also reset ssrc*/
	ch->SenderSSRC = 0;
	ch->first_SR = 1;
}


GF_Err gf_rtp_set_info_rtp(GF_RTPChannel *ch, u32 seq_num, u32 rtp_time, u32 ssrc)
{
	if (!ch) return GF_BAD_PARAM;
	ch->rtp_time = rtp_time;
	ch->last_pck_sn = 0;
	ch->rtp_first_SN = seq_num;
	ch->num_sn_loops = 0;
	//reset RTCP
	ch->ntp_init = 0;
	ch->first_SR = 1;
	ch->SenderSSRC = ssrc;
	ch->total_pck = ch->total_bytes = ch->last_num_pck_rcv = ch->last_num_pck_expected = ch->last_num_pck_loss = ch->tot_num_pck_rcv = ch->tot_num_pck_expected = ch->rtcp_bytes_sent = 0;
	return GF_OK;
}

GF_Err gf_rtp_initialize(GF_RTPChannel *ch, u32 UDPBufferSize, Bool IsSource, u32 PathMTU, u32 ReorederingSize, u32 MaxReorderDelay, char *local_interface_ip)
{
	GF_Err e;

	if (IsSource && !PathMTU) return GF_BAD_PARAM;

	if (ch->rtp) gf_sk_del(ch->rtp);
	if (ch->rtcp) gf_sk_del(ch->rtcp);
	if (ch->po) gf_rtp_reorderer_del(ch->po);

	ch->CurrentTime = 0;
	ch->rtp_time = 0;

	//create sockets for RTP/AVP profile only
	if (ch->net_info.Profile && 
		( !stricmp(ch->net_info.Profile, GF_RTSP_PROFILE_RTP_AVP) 
		|| !stricmp(ch->net_info.Profile, "RTP/AVP/UDP")
		|| !stricmp(ch->net_info.Profile, "RTP/SAVP")
		)
		) {
		//destination MUST be specified for unicast
		if (IsSource && ch->net_info.IsUnicast && !ch->net_info.destination) return GF_BAD_PARAM;

		//
		//	RTP
		//
		ch->rtp = gf_sk_new(GF_SOCK_TYPE_UDP);
		if (!ch->rtp) return GF_IP_NETWORK_FAILURE;
		if (ch->net_info.IsUnicast) {
			//if client, bind and connect the socket
			if (!IsSource) {
				e = gf_sk_bind(ch->rtp, ch->net_info.client_port_first, 1);
				if (e) return e;
				e = gf_sk_connect(ch->rtp, ch->net_info.source, ch->net_info.port_first);
				if (e) return e;
			}
			//else bind and set remote destination
			else {
				e = gf_sk_bind(ch->rtp, ch->net_info.port_first, 1);
				if (e) return e;
				e = gf_sk_set_remote_address(ch->rtp, ch->net_info.destination);
				if (e) return e;
				e = gf_sk_set_remote_port(ch->rtp, ch->net_info.client_port_first);
				if (e) return e;
			}
		} else {
			//Bind to multicast (auto-join the group). 
			//we do not bind the socket if this is a source-only channel because some servers
			//don't like that on local loop ...
			e = gf_sk_setup_multicast(ch->rtp, ch->net_info.source, ch->net_info.port_first, ch->net_info.TTL, (IsSource==2), local_interface_ip);
			if (e) return e;
		
			//destination is used for multicast interface addressing - TO DO

		}
		if (UDPBufferSize) gf_sk_set_buffer_size(ch->rtp, IsSource, UDPBufferSize);

		if (IsSource) {
			if (ch->send_buffer) free(ch->send_buffer);
			ch->send_buffer = malloc(sizeof(char) * PathMTU);
			ch->send_buffer_size = PathMTU;
		}
		

		//create re-ordering queue for UDP only, and recieve
		if (ReorederingSize && !IsSource) {
			if (!MaxReorderDelay) MaxReorderDelay = 200;
			ch->po = gf_rtp_reorderer_new(ReorederingSize, MaxReorderDelay);
		}

		//
		//	RTCP
		//
		ch->rtcp = gf_sk_new(GF_SOCK_TYPE_UDP);
		if (!ch->rtcp) return GF_IP_NETWORK_FAILURE;
		if (ch->net_info.IsUnicast) {
			if (!IsSource) {
				e = gf_sk_bind(ch->rtcp, ch->net_info.client_port_last, 1);
				if (e) return e;
				e = gf_sk_connect(ch->rtcp, ch->net_info.source, ch->net_info.port_last);
				if (e) return e;
			} else {
				e = gf_sk_bind(ch->rtcp, ch->net_info.port_last, 1);
				if (e) return e;
				e = gf_sk_set_remote_address(ch->rtcp, ch->net_info.destination);
				if (e) return e;
				e = gf_sk_set_remote_port(ch->rtcp, ch->net_info.client_port_last);
				if (e) return e;
			}
		} else {
			//Bind to multicast (auto-join the group)
			e = gf_sk_setup_multicast(ch->rtcp, ch->net_info.source, ch->net_info.port_last, ch->net_info.TTL, (IsSource==2), local_interface_ip);
			if (e) return e;
			//destination is used for multicast interface addressing - TO DO
		}
	}
		
	//format CNAME if not done yet
	if (!ch->CName) {
		//this is the real CName setup
		if (!ch->rtp) {
			ch->CName = strdup("mpeg4rtp");
		} else {
			void gf_get_user_name(char *buf, u32 buf_size);
			char name[GF_MAX_IP_NAME_LEN];

			s32 start;
			gf_get_user_name(name, 1024);
			if (strlen(name)) strcat(name, "@");
			start = strlen(name);
			//get host IP or loopback if error
			if (gf_sk_get_local_ip(ch->rtp, name+start) != GF_OK) strcpy(name+start, "127.0.0.1");
			ch->CName = strdup(name);
		}
	}
	
	return GF_OK;
}

/*get the UTC time expressed in RTP timescale*/
u32 gf_rtp_channel_time(GF_RTPChannel *ch)
{
	u32 sec, frac, res;
	gf_net_get_ntp(&sec, &frac);
	res = ( (u32) ( (frac>>26)*ch->TimeScale) ) >> 6;
	res += ch->TimeScale*(sec - ch->ntp_init);
	return (u32) res;
}

u32 gf_rtp_get_report_time()
{
	u32 sec, frac;
	gf_net_get_ntp(&sec, &frac);
	/*in units of 1/65536 seconds*/
	return (u32) ( (frac>>16) + 0x10000L*sec );
}


void gf_rtp_get_next_report_time(GF_RTPChannel *ch)
{
	Double d;

	/*offset between .5 and 1.5 sec*/
	d = 0.5 + ((Double) gf_rand()) / ((Double) RAND_MAX);
	/*of a minimal 5sec interval expressed in 1/65536 of a sec*/
	d = 5.0 * d * 65536;
	/*we should estimate bandwidth sharing too, but as we only support one sender*/
	ch->next_report_time = gf_rtp_get_report_time() + (u32) d;
}


u32 gf_rtp_read_rtp(GF_RTPChannel *ch, char *buffer, u32 buffer_size)
{
	GF_Err e;
	u32 seq_num, res;
	char *pck;

	//only if the socket exist (otherwise RTSP interleaved channel)
	if (!ch || !ch->rtp) return 0;

	e = gf_sk_receive(ch->rtp, buffer, buffer_size, 0, &res);
	if (!res || e || (res < 12)) res = 0;

	//add the packet to our Queue if any
	if (ch->po) {
		if (res) {
			seq_num = ((buffer[2] << 8) & 0xFF00) | (buffer[3] & 0xFF);
			gf_rtp_reorderer_add(ch->po, (void *) buffer, res, seq_num);
		}

		//pck queue may need to be flushed
		pck = gf_rtp_reorderer_get(ch->po, &res);
		if (pck) {
			memcpy(buffer, pck, res);
			free(pck);
		}
	}
	return res;
}


GF_Err gf_rtp_decode_rtp(GF_RTPChannel *ch, char *pck, u32 pck_size, GF_RTPHeader *rtp_hdr, u32 *PayloadStart)
{
	GF_Err e;
	s32 deviance, delta;
	u32 CurrSeq, LastSeq;
	u32 ntp, lost, low16;

	if (!rtp_hdr) return GF_BAD_PARAM;
	e = GF_OK;

	//we need to uncompress the RTP header
	rtp_hdr->Version = (pck[0] & 0xC0 ) >> 6;
	if (rtp_hdr->Version != 2) return GF_NOT_SUPPORTED;

	rtp_hdr->Padding = ( pck[0] & 0x20 ) >> 5;
	rtp_hdr->Extension = ( pck[0] & 0x10 ) >> 4;
	rtp_hdr->CSRCCount = pck[0] & 0x0F;
	rtp_hdr->Marker = ( pck[1] & 0x80 ) >> 7;
	rtp_hdr->PayloadType = pck[1] & 0x7F;

	/*we don't support multiple CSRC now. Only one source (the server) is allowed*/
	if (rtp_hdr->CSRCCount) return GF_NOT_SUPPORTED;
	/*SeqNum*/
	rtp_hdr->SequenceNumber = ((pck[2] << 8) & 0xFF00) | (pck[3] & 0xFF);
	/*TS*/
	rtp_hdr->TimeStamp = (u32) ((pck[4]<<24) &0xFF000000) | ((pck[5]<<16) & 0xFF0000) | ((pck[6]<<8) & 0xFF00) | ((pck[7]) & 0xFF);
	/*SSRC*/
	rtp_hdr->SSRC = ((pck[8]<<24) &0xFF000000) | ((pck[9]<<16) & 0xFF0000) | ((pck[10]<<8) & 0xFF00) | ((pck[11]) & 0xFF);
	/*first we only work with one payload type...*/
	if (rtp_hdr->PayloadType != ch->PayloadType) return GF_NOT_SUPPORTED;

	/*update RTP time if we didn't get the info*/
	if (!ch->rtp_time) {
		ch->rtp_time = rtp_hdr->TimeStamp;
		ch->rtp_first_SN = rtp_hdr->SequenceNumber;
		ch->num_sn_loops = 0;
	}

	if (!ch->ntp_init && ch->SenderSSRC && (ch->SenderSSRC != rtp_hdr->SSRC) ) {
		//if (ch->rtp_log ) fprintf(ch->rtp_log, "SSRC mismatch: %d vs %d\n", rtp_hdr->SSRC, ch->SenderSSRC);
		return GF_IP_NETWORK_EMPTY;
	}


	/*RTP specs annexe A.8*/
	if (!ch->ntp_init) {
		gf_net_get_ntp(&ch->ntp_init, &lost);
		ch->last_pck_sn = (u32) rtp_hdr->SequenceNumber-1;
	}
	/*this is a loop in SN - add it*/
	if ( (ch->last_pck_sn + 1 > rtp_hdr->SequenceNumber) 
		&& (rtp_hdr->SequenceNumber >= ch->last_pck_sn + MAX_RTP_SN/2)) {
		ch->num_sn_loops += 1;
	}
	
	ntp = gf_rtp_channel_time(ch);
	deviance = ntp - rtp_hdr->TimeStamp;
	delta = deviance - ch->last_deviance;
	ch->last_deviance = deviance;

	if (delta < 0) delta = -delta;
	ch->Jitter += delta - ( (ch->Jitter + 8) >> 4);

	lost = 0;
	LastSeq = ch->last_pck_sn;
	CurrSeq = (u32) rtp_hdr->SequenceNumber;
	/*next sequential pck*/
	if ( ( (LastSeq + 1) & 0xffff ) == CurrSeq ) {	
		ch->last_num_pck_rcv += 1;
		ch->last_num_pck_expected += 1;
	}
	/*repeated pck*/
	else if ( (LastSeq & 0xffff ) == CurrSeq ) {
		ch->last_num_pck_rcv += 1;
	}
	/*drop pck*/
	else {
		low16 = LastSeq & 0xffff;
		if ( CurrSeq > low16 )
			lost = CurrSeq - low16;
		else
			lost = 0xffff - low16 + CurrSeq + 1;

		ch->last_num_pck_expected += lost;
		ch->last_num_pck_rcv += 1;
		ch->last_num_pck_loss += lost;
	}
	ch->last_pck_sn = CurrSeq;


	if (ch->rtp_log) {
#if 0
		if (ch->last_pck_sn + 1 != rtp_hdr->SequenceNumber) 
			fprintf(ch->rtp_log, "RTP Pck Loss %d -> %d\n", ch->last_pck_sn, rtp_hdr->SequenceNumber);
#else
		ch->total_pck++;
		ch->total_bytes += pck_size-12;

		fprintf(ch->rtp_log, "RTP\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
									ch->SenderSSRC,
									rtp_hdr->TimeStamp,
									rtp_hdr->SequenceNumber,
									ntp,
									delta,
									ch->Jitter >> 4,
									lost,
									ch->total_pck,
									ch->total_bytes
				);
#endif
	}

	//we work with no CSRC so payload offset is always 12
	*PayloadStart = 12;

	//store the time
	ch->CurrentTime = rtp_hdr->TimeStamp;
	return e;
}


Double gf_rtp_get_current_time(GF_RTPChannel *ch)
{
	Double ret;
	if (!ch) return 0.0;
	ret = (Double) ch->CurrentTime;
	ret -= (Double) ch->rtp_time;
	ret /= ch->TimeScale;
	return ret;
}






GF_Err gf_rtp_send_packet(GF_RTPChannel *ch, GF_RTPHeader *rtp_hdr, char *extra_header, u32 extra_header_size, char *pck, u32 pck_size)
{
	GF_Err e;
	u32 Start, i;
	GF_BitStream *bs;

	if (!ch || !rtp_hdr 
		|| !ch->send_buffer 
		|| !pck 
		|| (rtp_hdr->CSRCCount && !rtp_hdr->CSRC) 
		|| (rtp_hdr->CSRCCount > 15)) return GF_BAD_PARAM;
	
	if (12 + extra_header_size + pck_size + 4*rtp_hdr->CSRCCount > ch->send_buffer_size) return GF_IO_ERR; 

	//we don't support multiple CSRC now. Only one source (the server) is allowed
	if (rtp_hdr->CSRCCount) return GF_NOT_SUPPORTED;

	bs = gf_bs_new(ch->send_buffer, ch->send_buffer_size, GF_BITSTREAM_WRITE);
	
	//write header
	gf_bs_write_int(bs, rtp_hdr->Version, 2);
	gf_bs_write_int(bs, rtp_hdr->Padding, 1);
	gf_bs_write_int(bs, rtp_hdr->Extension, 1);
	gf_bs_write_int(bs, rtp_hdr->CSRCCount, 4);
	gf_bs_write_int(bs, rtp_hdr->Marker, 1);
	gf_bs_write_int(bs, rtp_hdr->PayloadType, 7);
	gf_bs_write_u16(bs, rtp_hdr->SequenceNumber);
	gf_bs_write_u32(bs, rtp_hdr->TimeStamp);
	gf_bs_write_u32(bs, rtp_hdr->SSRC);

	for (i=0; i<rtp_hdr->CSRCCount; i++) {
		gf_bs_write_u32(bs, rtp_hdr->CSRC[i]);
	}
	//nb: RTP header is always aligned
	Start = (u32) gf_bs_get_position(bs);
	gf_bs_del(bs);

	//extra header
	if (extra_header_size) {
		memcpy(ch->send_buffer + Start, extra_header, extra_header_size);
		Start += extra_header_size;
	}
	//payload
	memcpy(ch->send_buffer + Start, pck, pck_size);
	e = gf_sk_send_to(ch->rtp, ch->send_buffer, Start + pck_size, NULL, 0);
	if (e) return e;

	//Update RTCP for sender reports
	ch->pck_sent_since_last_sr += 1;
	if (ch->first_SR) {
		//get a new report time
		gf_rtp_get_next_report_time(ch);
		ch->num_payload_bytes = 0;
		ch->num_pck_sent = 0;
		ch->first_SR = 0;
	}

	ch->num_payload_bytes += pck_size + extra_header_size;
	ch->num_pck_sent += 1;
	//store timing
	ch->last_pck_ts = rtp_hdr->TimeStamp;
	gf_net_get_ntp(&ch->last_pck_ntp_sec, &ch->last_pck_ntp_frac);
	return GF_OK;
}

u32 gf_rtp_is_unicast(GF_RTPChannel *ch)
{
	if (!ch) return 0;
	return ch->net_info.IsUnicast;
}

u32 gf_rtp_is_interleaved(GF_RTPChannel *ch)
{
	if (!ch || !ch->net_info.Profile) return 0;
	return ch->net_info.IsInterleaved;
}

u32 gf_rtp_get_clockrate(GF_RTPChannel *ch)
{
	if (!ch || !ch->TimeScale) return 0;
	return ch->TimeScale;
}

u32 gf_rtp_is_active(GF_RTPChannel *ch)
{
	if (!ch) return 0;
	if (!ch->rtp_first_SN && !ch->rtp_time) return 0;
	return 1;
}

u8 gf_rtp_get_low_interleave_id(GF_RTPChannel *ch)
{
	if (!ch || !ch->net_info.IsInterleaved) return 0;
	return ch->net_info.rtpID;
}

u8 gf_rtp_get_hight_interleave_id(GF_RTPChannel *ch)
{
	if (!ch || !ch->net_info.IsInterleaved) return 0;
	return ch->net_info.rtcpID;
}


#define RTP_DEFAULT_FIRSTPORT		7040

static u16 NextAvailablePort = RTP_DEFAULT_FIRSTPORT;

GF_Err gf_rtp_set_ports(GF_RTPChannel *ch)
{
	u32 retry;
	u16 p = NextAvailablePort;
	GF_Socket *sock;
	if (!ch) return GF_BAD_PARAM;

	if (ch->net_info.client_port_first) return GF_OK;

	sock = gf_sk_new(GF_SOCK_TYPE_UDP);
	if (!sock) return GF_IO_ERR;

	/*should be way enough (more than 100 rtp streams open on the machine)*/
	retry = 100;
	while (1) {
		/*try to bind without reuse. If fails this means the port is used on the machine, don't reuse it*/
		GF_Err e = gf_sk_bind(sock, p, 0);
		if (e==GF_OK) break;
		if (e!=GF_IP_CONNECTION_FAILURE) {
			gf_sk_del(sock);
			return GF_IP_NETWORK_FAILURE;
		}
		p+=2;
	}
	gf_sk_del(sock);
	ch->net_info.client_port_first = p;
	ch->net_info.client_port_last = p + 1;
	NextAvailablePort = p + 2;
	return GF_OK;
}


GF_Err gf_rtp_setup_payload(GF_RTPChannel *ch, GF_RTPMap *map)
{
	if (!ch || !map) return GF_BAD_PARAM;
	ch->PayloadType = map->PayloadType;
	strcpy(ch->PayloadName, map->payload_name ? map->payload_name : "");
	ch->TimeScale = map->ClockRate;
	return GF_OK;
}

GF_RTSPTransport *gf_rtp_get_transport(GF_RTPChannel *ch)
{
	if (!ch) return NULL;
	return &ch->net_info;
}

u32 gf_rtp_get_local_ssrc(GF_RTPChannel *ch)
{
	if (!ch) return 0;
	return ch->SSRC;
}


void gf_rtp_set_log(GF_RTPChannel *ch, FILE *log)
{
	if (ch) ch->rtp_log = log;
	if (log) {
		fprintf(log,	"#RTP log format:\n"
						"#RTP SenderSSRC RTP_TimeStamp RTP_SeqNum NTP@Recv Deviance Jitter NbLost NbTotPck NbTotBytes\n"
						"#RTCP Sender reports log format:\n"
						"#RTCP-SR SenderSSRC RTP_TimeStamp@NTP NbTotPck NbTotBytes NTP\n"
						"#RTCP Receiver reports log format:\n"
						"#RTCP-RR StreamSSRC Jitter ExtendedSeqNum ExpectDiff LossDiff NTP\n"
				);
	}
}

Float gf_rtp_get_loss(GF_RTPChannel *ch)
{
	if (!ch->tot_num_pck_expected) return 0.0f;
	return 100.0f - (100.0f * ch->tot_num_pck_rcv) / ch->tot_num_pck_expected;
}

u32 gf_rtp_get_tcp_bytes_sent(GF_RTPChannel *ch)
{
	return ch->rtcp_bytes_sent;
}

void gf_rtp_get_ports(GF_RTPChannel *ch, u16 *rtp_port, u16 *rtcp_port)
{
	*rtp_port = ch->net_info.client_port_first;
	*rtcp_port = ch->net_info.client_port_last;
}


/*
	RTP packet reorderer
*/

#define SN_CHECK_OFFSET		0x0A


#define REORDER_DEBUG	0

GF_RTPReorder *gf_rtp_reorderer_new(u32 MaxCount, u32 MaxDelay)
{
	GF_RTPReorder *tmp;
	
	if (MaxCount <= 1 || !MaxDelay) return NULL;

	tmp = malloc(sizeof(GF_RTPReorder));
	memset(tmp, 0, sizeof(GF_RTPReorder));
	tmp->MaxCount = MaxCount;
	tmp->MaxDelay = MaxDelay;
	return tmp;
}

static void DelItem(GF_POItem *it)
{
	if (it) {
		if (it->next) DelItem(it->next);
		free(it->pck);
		free(it);
	}
}


void gf_rtp_reorderer_del(GF_RTPReorder *po)
{
	if (po->in) DelItem(po->in);
	free(po);
}

void gf_rtp_reorderer_reset(GF_RTPReorder *po)
{
	if (!po) return;

	if (po->in) DelItem(po->in);
	po->head_seqnum = 0;
	po->Count = 0;
	po->IsInit = 0;
	po->in = NULL;
}

GF_Err gf_rtp_reorderer_add(GF_RTPReorder *po, void *pck, u32 pck_size, u32 pck_seqnum)
{
	GF_POItem *it, *cur;
	u32 bounds;

	if (!po) return GF_BAD_PARAM;

	it = malloc(sizeof(GF_POItem));
	it->pck_seq_num = pck_seqnum;
	it->next = NULL;
	it->size = pck_size;
	it->pck = malloc(pck_size);
	memcpy(it->pck, pck, pck_size);
	/*reset timeout*/
	po->LastTime = 0;

	//no input, this packet will be the input
	if (!po->in) {
		//the seq num was not initialized
		if (!po->head_seqnum) {
			po->head_seqnum = pck_seqnum;
		} else if (!po->IsInit) {
			//this is not in our current range for init
			if (ABSDIFF(po->head_seqnum, pck_seqnum) > SN_CHECK_OFFSET) goto discard;
			po->IsInit = 1;
		}

		po->in = it;
		po->Count += 1;
		return GF_OK;
	}

	//this is 16 bitr seq num, as we work with RTP only for now
	bounds = 0;
	if ( (po->head_seqnum >= 0xf000 ) || (po->head_seqnum <= 0x1000) ) bounds = 0x2000;

	//first check the head of the list
	//same seq num, we drop
	if (po->in->pck_seq_num == pck_seqnum) goto discard;

	if ( ( (u16) (pck_seqnum + bounds) <= (u16) (po->in->pck_seq_num + bounds) )
		&& ( (u16) (pck_seqnum + bounds) >= (u16) (po->head_seqnum + bounds)) ) {

		it->next = po->in;
		po->in = it;
		po->Count += 1;
#if REORDER_DEBUG
		fprintf(stdout, "INSERTING AT HEAD\n");
#endif
		return GF_OK;
	}

	//no, insert at the right place
	cur = po->in;

	while (1) {
		//same seq num, we drop
		if (cur->pck_seq_num == pck_seqnum) goto discard;

		//end of list
		if (!cur->next) {
			cur->next = it;
			po->Count += 1;
#if REORDER_DEBUG
			if (cur->pck_seq_num +1 != it->pck_seq_num) 
				fprintf(stdout, "!! Got %d expected %d\n", cur->pck_seq_num+1, it->pck_seq_num);
#endif
			//done
			return GF_OK;
		}

		//are we in the bounds ??
		if ( ( (u16) (cur->pck_seq_num + bounds) < (u16) (pck_seqnum + bounds) )
			&& ( (u16) (pck_seqnum + bounds) < (u16) (cur->next->pck_seq_num + bounds)) ) {

			//insert
			it->next = cur->next;
			cur->next = it;
			po->Count += 1;
#if REORDER_DEBUG
			fprintf(stdout, "INSERTING\n");
#endif
			//done
			return GF_OK;
		}
		cur = cur->next;
	}
	

discard:
	free(it->pck);
	free(it);
#if REORDER_DEBUG
	fprintf(stdout, "DROP");
#endif
	return GF_OK;
}

//retrieve the first available packet. Note that the behavior will be undefined if the first
//ever recieved packet if its SeqNum was unknown
//the BUFFER is yours, you must delete it
void *gf_rtp_reorderer_get(GF_RTPReorder *po, u32 *pck_size)
{
	GF_POItem *t;
	u32 bounds;
	void *ret;

	if (!po || !pck_size) return NULL;

	*pck_size = 0;

	//empty queue
	if (!po->in) return NULL;

	//check we have recieved the first packet
	if ( po->head_seqnum && po->MaxCount
		&& (po->MaxCount > po->Count) 
		&& (po->in->pck_seq_num != po->head_seqnum)) 
		return NULL;

	//no entry
	if (!po->in->next) goto check_timeout;

	bounds = 0;
	if ( (po->head_seqnum >= 0xf000 ) || (po->head_seqnum <= 0x1000) ) bounds = 0x2000;

	//release the output if SN in order or maxCount reached
	if (( (u16) (po->in->pck_seq_num + bounds + 1) == (u16) (po->in->next->pck_seq_num + bounds)) 
		|| (po->MaxCount && po->Count == po->MaxCount) ) {

#if REORDER_DEBUG
		if (po->in->pck_seq_num + 1 != po->in->next->pck_seq_num) 
			fprintf(stdout, "Fetched %d expected %d\n", po->in->pck_seq_num + 1, po->in->next->pck_seq_num);
#endif
		goto send_it;
	}
	//update timing
	else {
check_timeout:
		if (!po->LastTime) {
			po->LastTime = gf_sys_clock();
#if REORDER_DEBUG
			fprintf(stdout, "starting reorder timeout\n");
#endif
			return NULL;
		}
		//if exceeding the delay send the head
		if (gf_sys_clock() - po->LastTime >= po->MaxDelay) {
#if REORDER_DEBUG
			fprintf(stdout, "RTP Forcing output after %d ms wait (max allowed %d)\n", gf_sys_clock() - po->LastTime, po->MaxDelay);
#endif
			goto send_it;
		}
	}
	return NULL;


send_it:
	*pck_size = po->in->size;
	t = po->in;
	po->in = po->in->next;
	//no other output. reset the head seqnum
	po->head_seqnum = po->in ? po->in->pck_seq_num : 0;
	po->Count -= 1;
	//release the item
	ret = t->pck;
	free(t);
	return ret;
}
