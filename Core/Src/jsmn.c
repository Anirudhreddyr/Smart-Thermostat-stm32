/*
 * jsmn.c
 *
 *  Created on: Apr 30, 2026
 *      Author: anirudhr
 */
#include "jsmn.h"

/* Allocate token */
static jsmntok_t *jsmn_alloc_token(jsmn_parser *parser,
                                   jsmntok_t *tokens,
                                   size_t num_tokens) {
    if (parser->toknext >= num_tokens) return NULL;
    jsmntok_t *tok = &tokens[parser->toknext++];
    tok->start = tok->end = -1;
    tok->size = 0;
    return tok;
}

/* Fill token */
static void jsmn_fill_token(jsmntok_t *token,
                            jsmntype_t type,
                            int start,
                            int end) {
    token->type = type;
    token->start = start;
    token->end = end;
    token->size = 0;
}

/* Parse primitive (numbers, true, false) */
static int jsmn_parse_primitive(jsmn_parser *parser,
                                const char *js,
                                size_t len,
                                jsmntok_t *tokens,
                                size_t num_tokens) {
    int start = parser->pos;

    for (; parser->pos < len; parser->pos++) {
        char c = js[parser->pos];
        if (c == ',' || c == '}' || c == ']' || c == ' ' || c == '\n') break;
    }

    jsmntok_t *token = jsmn_alloc_token(parser, tokens, num_tokens);
    if (!token) return -1;

    jsmn_fill_token(token, JSMN_PRIMITIVE, start, parser->pos);
    parser->pos--;

    return 0;
}

/* Parse string */
static int jsmn_parse_string(jsmn_parser *parser,
                              const char *js,
                              size_t len,
                              jsmntok_t *tokens,
                              size_t num_tokens) {
    int start = parser->pos;

    parser->pos++;

    for (; parser->pos < len; parser->pos++) {
        if (js[parser->pos] == '\"') {
            jsmntok_t *token = jsmn_alloc_token(parser, tokens, num_tokens);
            if (!token) return -1;

            jsmn_fill_token(token, JSMN_STRING, start + 1, parser->pos);
            return 0;
        }
    }

    return -1;
}

/* Main parse function */
int jsmn_parse(jsmn_parser *parser,
               const char *js,
               size_t len,
               jsmntok_t *tokens,
               unsigned int num_tokens) {

    for (; parser->pos < len; parser->pos++) {

        char c = js[parser->pos];

        switch (c) {

        case '{':
        case '[': {
            jsmntok_t *token = jsmn_alloc_token(parser, tokens, num_tokens);
            if (!token) return -1;

            token->type = (c == '{' ? JSMN_OBJECT : JSMN_ARRAY);
            token->start = parser->pos;
            parser->toksuper = parser->toknext - 1;
            break;
        }

        case '}':
        case ']': {
            for (int i = parser->toknext - 1; i >= 0; i--) {
                if (tokens[i].start != -1 && tokens[i].end == -1) {
                    tokens[i].end = parser->pos + 1;
                    parser->toksuper = -1;
                    break;
                }
            }
            break;
        }

        case '\"':
            if (jsmn_parse_string(parser, js, len, tokens, num_tokens) < 0)
                return -1;
            break;

        case '\t': case '\r': case '\n': case ' ':
            break;

        case ':':
            break;

        case ',':
            break;

        default:
            if (jsmn_parse_primitive(parser, js, len, tokens, num_tokens) < 0)
                return -1;
            break;
        }
    }

    return parser->toknext;
}

/* Initialize parser */
void jsmn_init(jsmn_parser *parser) {
    parser->pos = 0;
    parser->toknext = 0;
    parser->toksuper = -1;
}


