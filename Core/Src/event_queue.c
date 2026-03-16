/*
 * event_queue.c
 *
 *  Created on: Mar 16, 2026
 *      Author: anirudhr
 */
#include <stdint.h>
#include "event_queue.h"

static event_t queue[EVENT_QUEUE_SIZE];
static uint8_t head = 0;
static uint8_t tail = 0;
static uint8_t count = 0;

void event_queue_init(void)
{
	head = 0;
	tail = 0;
	count = 0;
}

int event_queue_push(event_t event)
{
	if (count >= EVENT_QUEUE_SIZE)
		return -1;

	queue[tail] = event;
	tail = (tail + 1) % EVENT_QUEUE_SIZE;
	count++;

	return 0;
}

int event_queue_pop(event_t *event)
{
	if (count == 0)
		return -1;

	*event = queue[head];
	head = (head + 1) % EVENT_QUEUE_SIZE;
	count--;

	return 0;
}
