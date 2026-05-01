/*
 * logger.h
 *
 *  Created on: Apr 29, 2026
 *      Author: anirudhr
 */

#ifndef LOGGER_H
#define LOGGER_H

#include <stdint.h>

/* Log Levels */
typedef enum
{
    LOG_LEVEL_INFO,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_DEBUG
} log_level_t;

/* Main logging function */
void log_print(log_level_t level, const char *format, ...);

/* Macros for easy usage */
#define LOG_INFO(...)   log_print(LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_ERROR(...)  log_print(LOG_LEVEL_ERROR, __VA_ARGS__)
#define LOG_DEBUG(...)  log_print(LOG_LEVEL_DEBUG, __VA_ARGS__)

#endif /* LOGGER_H */
