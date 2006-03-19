/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005
 *					All rights reserved
 *
 *  This file is part of GPAC / MP4 reader module
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


#ifndef _ISMO_IN_H_
#define _ISMO_IN_H_

#include <gpac/modules/service.h>
#include <gpac/media_tools.h>
#include <gpac/constants.h>

/*
			reader module

*/

typedef struct
{
	/*the service we're responsible for*/
	GF_ClientService *service;

	/*current channels*/
	GF_List *channels;

	/*input file*/
	GF_ISOFile *mov;
	u32 time_scale;

	/*remote file handling*/
	GF_DownloadSession * dnload;
	u64 missing_bytes, last_size;

	/*if set, work with dynamic OD mode: scene graph will be generated by the app based
	on the content of the OD AU (eg all streams in file)*/
	u16 OD_ESID;
	char *od_au;
	u32 od_au_size;

	u32 base_track_id;
} ISOMReader;


typedef struct
{
	u32 track;
	LPNETCHANNEL channel;
	ISOMReader *owner;
	u64 duration;


	/*current sample*/
	GF_ISOSample *sample;
	GF_SLHeader current_slh;
	GF_Err last_state;

	Bool is_pulling;

	Bool has_edit_list;
	u32 sample_num;
	u64 sample_time;
	u32 start, end;
	Double speed;

	u32 time_scale;
	Bool to_init, is_playing;
	u8 streamType;
	
	u16 FAKE_ESID;

	Bool is_encrypted;

	/*cache stuff*/
	u64 cache_seed_ts;
	u32 frame_cts_offset;
	u64 prev_dts, max_cts;
	GF_ISOSample *cache_sample;
} ISOMChannel;
void isor_reset_reader(ISOMChannel *ch);
void isor_reader_get_sample(ISOMChannel *ch);
void isor_reader_release_sample(ISOMChannel *ch);

ISOMChannel *isor_get_channel(ISOMReader *reader, LPNETCHANNEL channel);

GF_InputService *isor_client_load();
void isor_client_del(GF_BaseInterface *bi);

GF_Descriptor *isor_emulate_iod(ISOMReader *read);
/*uses nero chapter info and remaps to MPEG-4 OCI if no OCI present in descriptor*/
void isor_emulate_chapters(GF_ISOFile *file, GF_InitialObjectDescriptor *iod);

#ifndef GPAC_READ_ONLY
GF_BaseInterface *isow_load_cache();
void isow_delete_cache(GF_BaseInterface *bi);
#endif


#endif

