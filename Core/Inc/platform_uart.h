/*
 * platform_uart.h
 *
 *  Created on: Mar 16, 2026
 *      Author: anirudhr
 */

#ifndef PLATFORM_UART_H
#define PLATFORM_UART_H

#include <stdint.h>

void platform_uart_init(void);
void platform_uart_send(const char *msg);

#endif /* PLATFORM_UART_H */
