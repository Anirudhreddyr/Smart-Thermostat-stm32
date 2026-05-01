/*
 * jsmn.h
 *
 *  Created on: Apr 30, 2026
 *      Author: anirudhr
 */

#ifndef JSMN_H
#define JSMN_H

#include <stddef.h>

typedef enum {
    JSMN_UNDEFINED = 0,
    JSMN_OBJECT = 1 << 0,
    JSMN_ARRAY  = 1 << 1,
    JSMN_STRING = 1 << 2,
    JSMN_PRIMITIVE = 1 << 3
} jsmntype_t;

typedef struct {
    jsmntype_t type;
    int start;
    int end;
    int size;
} jsmntok_t;

typedef struct {
    unsigned int pos;     /* current position in JSON string */
    unsigned int toknext; /* next token to allocate */
    int toksuper;         /* superior token node */
} jsmn_parser;

/* Initialize parser */
void jsmn_init(jsmn_parser *parser);

/* Parse JSON string */
int jsmn_parse(jsmn_parser *parser,
               const char *js,
               size_t len,
               jsmntok_t *tokens,
               unsigned int num_tokens);

#endif /* JSMN_H */

