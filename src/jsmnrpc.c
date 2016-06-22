/**
 * Copyright (c) Project Iota
 *
 * uCbor is licensed under an Apache license, version 2.0 license.
 * All rights not explicitly granted in the Apache license, version 2.0 are reserved.
 * See the included LICENSE file for more details.
 */

#include <stdio.h>
#include <string.h>
#include "jsmnrpc.h"

#define JSONRPC_MAGIC_KEY "jsonrpc"
#define JSONRPC_VER_KEY "2.0"
#define JSONRPC_METHOD_KEY "method"
#define JSONRPC_PARAMS_KEY "params"
#define JSONRPC_ID_KEY "id"
#define JSONRPC_NULL "null"


static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

int jrpcCall(char* req, char* rsp)
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
			/* We may use strndup() to fetch string value */
			printf("- Method: %.*s\n", t[i+1].end-t[i+1].start,
					req + t[i+1].start);
			i++;
		} else if (jsoneq(req, &t[i], JSONRPC_PARAMS_KEY) == 0) {
            int j;
			printf("- Params:\n");
			if (t[i+1].type != JSMN_ARRAY) {
				continue; /* We expect params to be an array of strings */
			}
			for (j = 0; j < t[i+1].size; j++) {
				jsmntok_t *g = &t[i+j+2];
				printf("  * %.*s\n", g->end - g->start, req + g->start);
			}
			i += t[i+1].size + 1;
		} else if (jsoneq(req, &t[i], JSONRPC_ID_KEY) == 0) {
            /* We may want to do strtol() here to get numeric value */
			printf("- Id: %.*s\n", t[i+1].end-t[i+1].start,
					req + t[i+1].start);
			i++;
		} else {
			printf("Unexpected key: %.*s\n", t[i].end-t[i].start,
					req + t[i].start);
		}
	}
	return 0;
}

