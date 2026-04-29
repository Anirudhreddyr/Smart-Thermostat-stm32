/*
 * thermostat_controller.c
 *
 *  Created on: Mar 16, 2026
 *      Author: anirudhr
 */
#include "main.h"
#include "thermostat_controller.h"
#include "event_queue.h"
#include "platform_uart.h"
#include "stm32f4xx_hal.h"

static int current_temp = 25;
static int target_temp = 25;

void thermostat_controller_init(void)
{
	platform_uart_send("Thermostat controller Ready\r\n");
}

void thermostat_controller_process_event(void)
{
	event_t event;

	if (event_queue_pop(&event) == 0){
		if (event.type == EVENT_SET_TEMPERATURE){
			target_temp = event.data;

			platform_uart_send("Target Temperature Updated\r\n");
		}

		if (event.type == EVENT_TEMP_UPDATE)
		{
			/* Simulate temperature reading */
			 current_temp = event.data; //Bug fixed  controller is IGNORING the	 data.

		#define HYSTERESIS 1

		static uint8_t heater_state = 0;

		if (heater_state == 0)
		{
			// Heater OFF → check ON
			if (current_temp <= (target_temp - HYSTERESIS))
			{
				HAL_GPIO_WritePin(GPIOA, HEATER_RELAY_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA, FAN_RELAY_Pin, GPIO_PIN_RESET);

				heater_state = 1;

				platform_uart_send("Heating ON\r\n");
			}
		}
		else
		{
			// Heater ON → check OFF
			if (current_temp >= (target_temp + HYSTERESIS))
			{
				HAL_GPIO_WritePin(GPIOA, HEATER_RELAY_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOA, FAN_RELAY_Pin, GPIO_PIN_SET);

				heater_state = 0;

				platform_uart_send("Cooling ON\r\n");
			}
		}
	  }
	}
}tes
