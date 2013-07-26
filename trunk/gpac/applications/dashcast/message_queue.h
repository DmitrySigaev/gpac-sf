/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Authors: Arash Shafiei
 *			Copyright (c) Telecom ParisTech 2000-2013
 *					All rights reserved
 *
 *  This file is part of GPAC / dashcast
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

#ifndef MESSAGE_QUEUE_H_
#define MESSAGE_QUEUE_H_

#define GPAC_THREAD
#ifdef WIN32
#define SEM
#endif

#include <string.h>
#include <stdlib.h>

#ifdef GPAC_THREAD
#include <gpac/thread.h>
#else
#include <pthread.h>
#endif

typedef struct MessageQueueNode {

	void * data;
	int size;
	struct MessageQueueNode * next;

} MessageQueueNode;

typedef struct MessageQueue {

	MessageQueueNode * last_node;
	MessageQueueNode * first_node;
	int nb_nodes;
#ifdef GPAC_THREAD
#ifdef SEM
	GF_Semaphore * sem;
#else
	GF_Condition * cond;
#endif
	GF_Mutex * mux;
#else
	pthread_mutex_t mux;
	pthread_cond_t cond;
#endif

} MessageQueue;

void dc_message_queue_init(MessageQueue *mq);
void dc_message_queue_put(MessageQueue *mq, void * data, int size);
int dc_message_queue_get(MessageQueue *mq, void * data);
void dc_message_queue_flush(MessageQueue *mq);
void dc_message_queue_free(MessageQueue *mq);

#endif /* MESSAGE_QUEUE_H_ */