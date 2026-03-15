/*
 * platform_uart.c
 *
 *  Created on: Mar 16, 2026
 *      Author: anirudhr
 */
#include "platform_uart.h"
#include "main.h"
#include <string.h>

extern UART_HandleTypeDef huart2;

void platform_uart_init(void)
{
	/* HAL already initialized UART in main.c */
}

void platform_uart_send(const char *msg)
{
	uint16_t len = strlen(msg);

	HAL_UART_Transmit(&huart2,
					  (uint8_t*)msg,
					  len,
					  HAL_MAX_DELAY);
}


