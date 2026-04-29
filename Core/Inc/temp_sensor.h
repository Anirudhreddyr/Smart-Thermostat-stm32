/*
 * temp_sensor.h
 *
 *  Created on: Apr 28, 2026
 *      Author: anirudhr
 */

#ifndef TEMP_SENSOR
#define TEMP_SENSOR

#include <stdint.h>

/* Initialize sensor */
void temp_sensor_init(void);

/* Read temperature value */
int temp_sensor_read(void);

/* Scheduler task for sensor update */
void temp_sensor_task(void);

#endif /* TEMP_SENSOR */
