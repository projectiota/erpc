/**
 * Copyright (c) Project Iota
 *
 * uCbor is licensed under an Apache license, version 2.0 license.
 * All rights not explicitly granted in the Apache license, version 2.0 are reserved.
 * See the included LICENSE file for more details.
 */
#include "jsmnrpc.h"
#include <stdio.h>


const char *req =
	"{\"jsonrpc\": \"2.0\", \"method\": \"digitalWrite\", "
	"\"params\": [\"users\", \"wheel\", \"audio\", \"video\"], \"id\": 1}";

char rsp[32];

int main ()
{
    printf("Hello test!\n");

    jrpcCall(req, rsp);

    return 0;
}
