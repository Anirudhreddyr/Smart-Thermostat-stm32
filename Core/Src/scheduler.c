/*
 * scheduler.c
 *
 *  Created on: Mar 16, 2026
 *      Author: anirudhr
 */

#include "scheduler.h"

typedef struct
{
	task_func_t task;
	uint32_t period;
	uint32_t counter;
} task_t;

static task_t task_list[MAX_TASKS];
static uint8_t task_count = 0;

void scheduler_init (void)
{
	task_count = 0;
}

void scheduler_add_task(task_func_t task, uint32_t period)
{
	if(task_count < MAX_TASKS)
	{
		task_list[task_count].task = task;
		task_list[task_count].period = period;
		task_list[task_count].counter = 0;
		task_count++;
	}
}

void scheduler_tick(void)
{
	for(uint8_t i = 0; i < task_count; i++)
	{
		task_list[i].counter++;
	}
}

void scheduler_run(void)
{
	for(uint8_t i = 0; i < task_count; i++)
	{
		if(task_list[i].counter >= task_list[i].period)
		{
			task_list[i].counter = 0;
			task_list[i].task();
		}
	}
}
