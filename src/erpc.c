/**
 * Copyright (c) Project Iota
 *
 * uCbor is licensed under an Apache license, version 2.0 license.
 * All rights not explicitly granted in the Apache license, version 2.0 are reserved.
 * See the included LICENSE file for more details.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jsmn.h"
#include "erpc.h"

#define JSONRPC_METHOD_KEY "fnc"
#define JSONRPC_PARAMS_KEY "params"
#define JSONRPC_REPLY_TO_KEY "rto"
#define JSONRPC_NULL "null"

/**
 * Globals
 */
static unsigned char fncCodeStr[8] = {0};
static unsigned char fncCode = 0;
static unsigned char params[8][16] = {0};
static unsigned char replyTo[32] = {0};
static unsigned char paramNb = 0;

/**
 * fncTable is the poiner to the array of function pointers.
 * When initialized, this poiner points to the table (array)
 * of function pointers that are installed by the user.
 */
void (*(*fncTable)[])(int argc, char *argv[]);

/**
 * Helper function to compare strings
 */
static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

/**
 * Parse JSON and call adequate function from lookup table
 */
int erpcCall(const char* req, char* rsp)
{
    int i;
    int r;
    jsmn_parser p;
    jsmntok_t t[128]; /* We expect no more than 128 tokens */

    jsmn_init(&p);

    printf(req);
    r = jsmn_parse(&p, req, strlen(req), t, sizeof(t)/sizeof(t[0]));
    if (r < 0) {
        printf("Failed to parse JSON: %d\n", r);
        return 1;
    }

    /* Assume the top-level element is an object */
    if (r < 1 || t[0].type != JSMN_OBJECT) {
        printf("Object expected\n");
        return 1;
    }

    /* Loop over all keys of the root object */
    for (i = 1; i < r; i++) {
        if (jsoneq(req, &t[i], JSONRPC_METHOD_KEY) == 0) {

            int size = t[i+1].end-t[i+1].start;
        
            /* We may use strndup() to fetch string value */
            memcpy(fncCodeStr, req + t[i+1].start, t[i+1].end-t[i+1].start);
            fncCodeStr[size] = '\0';
            fncCode = atoi(fncCodeStr);

            printf("- MethodCode: %d\n", fncCode);
            i++;
        } else if (jsoneq(req, &t[i], JSONRPC_PARAMS_KEY) == 0) {
            int j;

            printf("- Params:\n");
            /** Reset paramNb */
            paramNb = 0;

            if (t[i+1].type != JSMN_ARRAY) {
                continue; /* We expect params to be an array of strings */
            }
            for (j = 0; j < t[i+1].size; j++) {
                jsmntok_t *g = &t[i+j+2];
                int paramSize = g->end - g->start;
                memcpy(params[paramNb], req + g->start, paramSize);
                params[paramNb][paramSize] = '\0';

                printf("  * %s\n", params[paramNb]);
                paramNb++;
            }
            i += t[i+1].size + 1;
        } else if (jsoneq(req, &t[i], JSONRPC_REPLY_TO_KEY) == 0) {
            int size = t[i+1].end-t[i+1].start;

            /* We may want to do strtol() here to get numeric value */
            memcpy(replyTo, req + t[i+1].start, size);
            replyTo[size] = '\0';
            printf("- replyTo: %s\n", replyTo);
            i++;
        } else {
            printf("Unexpected key: %.*s\n", t[i].end-t[i].start,
            req + t[i].start);
        }
    }

    /** Call the function */
    (*fncTable)[fncCode](paramNb, params);
    return 0;
}

/**
 * Set function table:
 * user declares custom functions and stores them in the table
 * in his high level program, then tells erpc library to use these functions.
 *
 * Erpc is platform agnostic - it knows only to parse JSON and call
 * method with name `fncCode` with correct parameters. What will this method
 * actually do, it is on user to define.
 */
void erpcSetFncTable( void (*(*ft)[])(int argc, char *argv[]) )
{
    fncTable = ft;
}
