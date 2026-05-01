/*
 * logger.c
 *
 *  Created on: Apr 29, 2026
 *      Author: anirudhr
 */
#include "logger.h"
#include "platform_uart.h"
#include <stdio.h>
#include <stdarg.h>

/* Enable or disable logs */
#define LOG_ENABLE 1

void log_print(log_level_t level, const char *format, ...)
{
#if LOG_ENABLE

    char buffer[128];
    char prefix[10];

    /* Select log prefix */
    switch(level)
    {
        case LOG_LEVEL_INFO:
            sprintf(prefix, "[INFO] ");
            break;

        case LOG_LEVEL_ERROR:
            sprintf(prefix, "[ERROR] ");
            break;

        case LOG_LEVEL_DEBUG:
            sprintf(prefix, "[DEBUG] ");
            break;

        default:
            prefix[0] = '\0';
            break;
    }

    /* Format user message */
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    /* Combine prefix + message */
    char final_msg[160];
    snprintf(final_msg, sizeof(final_msg), "%s%s\r\n", prefix, buffer);

    /* Send over UART */
    platform_uart_send(final_msg);

#endif
}
