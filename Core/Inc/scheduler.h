/*
 * scheduler.h
 *
 *  Created on: Mar 16, 2026
 *      Author: anirudhr
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#define MAX_TASKS 5

typedef void (*task_func_t) (void);

void scheduler_init(void);
void scheduler_add_task(task_func_t task, uint32_t period);
void scheduler_run(void);
void shcduler_tick(void);

#endif /* SCHEDULER_H */
