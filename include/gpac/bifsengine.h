/*
 *					GPAC Multimedia Framework
 *
 *			Authors: Cyril Concolato - Jean le Feuvre
 *				Copyright (c) 2005-200X ENST
 *					All rights reserved
 *
 *  This file is part of GPAC / ISO Media File Format sub-project
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


#ifndef _GF_BIFSENGINE_H_
#define _GF_BIFSENGINE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <gpac/scene_manager.h>

#ifndef GPAC_DISABLE_BENG

typedef struct __tag_bifs_engine GF_BifsEngine;


typedef void (*gf_beng_callback)(void *udta, u16 ESID, char *data, u32 size, u64 ts);

/**
 * @calling_object is the calling object on which call back will be called
 * @inputContext is the name of a scene file (bt, xmt or mp4) to initialize the coding context
 *
 * must be called only one time (by process calling the DLL) before other calls
 */
GF_BifsEngine *gf_beng_init(void *calling_object, char *inputContext);

/**
 * @calling_object is the calling object on which call back will be called
 * @inputContext is an UTF-8 scene description (with or without IOD) in BT or XMT-A format
 * @width, @height: width and height of scene if no IOD is given in the context.
 * @usePixelMetrics: metrics system used in the scene, if no IOD is given in the context.
 *
 * must be called only one time (by process calling the DLL) before other calls
 */
GF_BifsEngine *gf_beng_init_from_string(void *calling_object, char *inputContext, u32 width, u32 height, Bool usePixelMetrics);


/**
 * @calling_object is the calling object on which call back will be called
 * @ctx is an already loaded scene manager
 *
 * must be called only one time (by process calling the DLL) before other calls
 */
GF_BifsEngine *gf_beng_init_from_context(void *calling_object, GF_SceneManager *ctx);

/**
 * @beng, pointer to the GF_BifsEngine returned by gf_beng_init()
 *
 * must be called after gf_beng_init()
 */
u32 gf_beng_get_stream_count(GF_BifsEngine *beng);

/**
 * @beng, pointer to the GF_BifsEngine returned by gf_beng_init()
 * @idx: stream index
 * @ESID: pointer to the stream ID
 * @config: pointer to the encoded BIFS config (memory is not allocated)
 * @config_len: length of the buffer
 * @streamType: pointer to get stream type
 * @objectType: pointer to get object type
 * @timeScale: pointer to get time scale
 *
 * must be called after gf_beng_init()
 */
GF_Err gf_beng_get_stream_config(GF_BifsEngine *beng, u32 idx, u16 *ESID, const char **config, u32 *config_len, u32 *streamType, u32 *objectType, u32 *timeScale);

/**
 * Encodes the AU context which is not encoded when calling BENC_EncodeAUFromString/File
 * Should be called after Aggregate.
 *
 * @beng, pointer to the GF_BifsEngine returned by gf_beng_init()
 * @AUCallback, pointer on a callback function to get the result of the coding the AU using the current context
 *
 */
GF_Err gf_beng_encode_context(GF_BifsEngine *beng, gf_beng_callback callback);

/**
 * @beng, pointer to the GF_BifsEngine returned by gf_beng_init()
 * @auFile, name of a file containing a description for an access unit (BT or XMT)
 * @AUCallback, pointer on a callback function to get the result of the coding the AU using the current context
 *
 */
GF_Err gf_beng_encode_from_file(GF_BifsEngine *beng, char *auFile, gf_beng_callback callback);

/**
 * @beng, pointer to the GF_BifsEngine returned by gf_beng_init()
 * @auString, a char string to encode (must one or several complete nodes in BT
 * @AUCallback, pointer on a callback function to get the result of the coding the AU using the current context
 *
 */
GF_Err gf_beng_encode_from_string(GF_BifsEngine *beng, char *auString, gf_beng_callback callback);

/**
 * @beng, pointer to the GF_BifsEngine returned by gf_beng_init()
 * @ctxFileName, name of the file to save the current state of the BIFS scene to
 *
 * save the current context of the beng.
 * if you want to save an aggregate context, use BENC_AggregateCurrentContext before
 *
 */
GF_Err gf_beng_save_context(GF_BifsEngine *beng, char *ctxFileName);

/**
 * @beng, pointer to the GF_BifsEngine returned by gf_beng_init()
 * @ESID, stream ID
 *
 * marks the first command of the first AU of the stream as 'never_apply'
 */
GF_Err gf_beng_mark_for_aggregation(GF_BifsEngine *codec, u16 ESID);

/**
 * @beng, pointer to the GF_BifsEngine returned by gf_beng_init()
 *
 * aggregates the current context of the beng, creates a scene replace
 *
 */
GF_Err gf_beng_aggregate_context(GF_BifsEngine *beng);

/**
 * @beng, pointer to the GF_BifsEngine returned by gf_beng_init()
 *
 * release the memory used by this beng, no more call on the beng should happen after this
 *
 */
void gf_beng_terminate(GF_BifsEngine *beng);


#endif /*GPAC_DISABLE_BENG*/


#ifdef __cplusplus
}
#endif // __cplusplus


#endif	/*_GF_BIFSENGINE_H_*/

