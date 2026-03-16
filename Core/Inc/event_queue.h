/*
 * Event_queue.h
 *
 *  Created on: Mar 16, 2026
 *      Author: anirudhr
 */
#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H

#include <stdint.h>

#define EVENT_QUEUE_SIZE 10

typedef enum
{
	EVENT_NONE = 0,
	EVENT_TEMP_UPDATE,
	EVENT_SET_TEMPERATURE,
	EVENT_AUTH_SUCCESS,
	EVENT_ENERGY_OPTIMIZE
} event_type_t;

typedef struct
{
	event_type_t type;
	int32_t data;
} event_t;

void event_queue_init(void);
int event_queue_push(event_t event);
int event_queue_pop(event_t *event);

#endif /* EVENT_QUEUE_H */
