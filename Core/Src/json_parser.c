/*
 * json_parser.c
 *
 *  Created on: Mar 16, 2026
 *      Author: anirudhr
 */
#include "json_parser.h"
#include "jsmn.h"
#include "event_queue.h"
#include "logger.h"

#include <string.h>
#include <stdlib.h>

/* Helper function to match JSON keys */
static int jsoneq(const char *json, jsmntok_t *tok, const char *key)
{
    return (tok->type == JSMN_STRING &&
            (int)strlen(key) == tok->end - tok->start &&
            strncmp(json + tok->start, key, tok->end - tok->start) == 0)
           ? 0 : -1;
}

void json_parse(char *json)
{
    jsmn_parser parser;
    jsmntok_t tokens[10];

    jsmn_init(&parser);

    int token_count = jsmn_parse(&parser, json, strlen(json), tokens, 10);

    /* Error handling */
    if (token_count < 0)
    {
        LOG_ERROR("JSON Parse Failed (invalid JSON)");
        return;
    }

    /* NEW: Ensure JSON is complete */
    if (parser.pos < strlen(json))
    {
        LOG_ERROR("Incomplete JSON Received");
        return;
    }

    /* Root should be object */
    if (token_count < 1 || tokens[0].type != JSMN_OBJECT)
    {
        LOG_ERROR("Invalid JSON Format");
        return;
    }

    /* Loop through tokens */
    for (int i = 1; i < token_count; i++)
    {
        /* Find key "value" */
        if (jsoneq(json, &tokens[i], "value") == 0)
        {
            /* Extract value */
            int temp = atoi(json + tokens[i + 1].start);

            /* Create event */
            event_t evt;
            evt.type = EVENT_SET_TEMPERATURE;
            evt.data = temp;

            event_queue_push(evt);

            LOG_INFO("JSON Temperature Parsed: %d", temp);

            i++; // Skip value token
        }
    }
}

