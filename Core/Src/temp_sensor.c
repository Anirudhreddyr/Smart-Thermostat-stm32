/*
 * temp_sensor.c
 *
 *  Created on: Apr 28, 2026
 *      Author: anirudhr
 */

#include "temp_sensor.h"
#include "event_queue.h"
#include "platform_uart.h"
#include <stdio.h>

/* Simulated temperature */
static int simulated_temp = 20;

/* Counter to generate periodic update */
static uint32_t counter = 0;

/* Initialization */
void temp_sensor_init(void)
{
    platform_uart_send("Temp Sensor Initialized\r\n");
}

/* Read function (currently simulated) */
int temp_sensor_read(void)
{
    return simulated_temp;
}

/* Scheduler task */
void temp_sensor_task(void)
{
    counter++;

    /* Generate temp update every 1 sec */
    if(counter >= 200)   // 200 × 5ms = 1 second
    {
        int temp = temp_sensor_read();

        event_t evt;
        evt.type = EVENT_TEMP_UPDATE;
        evt.data = temp;

        event_queue_push(evt);

        /* Debug print (safe frequency) */
        char buffer[32];
        sprintf(buffer, "Temp Update: %d\r\n", temp);
        platform_uart_send(buffer);

        /* Simulate temperature change */
        simulated_temp++;

        if(simulated_temp > 30)
            simulated_temp = 20;

        counter = 0;
    }
}

