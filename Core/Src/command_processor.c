/*
 * command_processor.c
 *
 *  Created on: Mar 16, 2026
 *      Author: anirudhr
 */

#include <stdint.h>
#include "command_processor.h"
#include "event_queue.h"
#include "platform_uart.h"
#include <string.h>
#include <stdlib.h>

void command_processor_init(void)
{
	platform_uart_send("Command Processor Ready\r\n");
}

void command_processor_process(char *cmd)
{
	event_t event;

	if (strncmp(cmd, "TEMP", 4) == 0)
	{
		int value = atoi(&cmd[5]);

		event.type = EVENT_SET_TEMPERATURE;
		event.data = value;

		platform_uart_send("Temperature Set Command Received\r\n");
	}
	else if (strncmp(cmd, "STATUS", 6) == 0)
	{
		event.type = EVENT_TEMP_UPDATE;
		event.data = 0;

		event_queue_push(event);

		platform_uart_send("Status Request Received\r\n");
	}
	else
	{
		platform_uart_send("Unknown command\r\n");
	}
}
