/**
 * Copyright (c) Project Iota
 *
 * uCbor is licensed under an Apache license, version 2.0 license.
 * All rights not explicitly granted in the Apache license, version 2.0 are reserved.
 * See the included LICENSE file for more details.
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "erpc.h"


const char *req =
	"{\"method\": \"digitalWrite\", "
	"\"params\": [\"users\", \"wheel\", \"audio\", \"video\"], \"rto\": \"/user/1234/out\"}";


void digitalWrite(int argc, char *argv[])
{
    uint8_t i = 0;
    PARAMS_t params = {{0}};

    memcpy(params, argv, sizeof(PARAMS_t));

    printf("FNC: digitalWrite()\n");
    for (i = 0; i < argc; i++)
        printf("%s\n", params[i]);
}

void digitalRead(int argc, char *argv[])
{
    printf("FNC: digitalRead()\n");
}


int main ()
{
    printf("Hello test!\n");

    /** Initialize function look-up table with our functions */
    erpcAddFunction("digitalWrite", digitalWrite);
    erpcAddFunction("digitalRead", digitalRead);

    /** Now we can call the function */
    erpcCall(req);

    return 0;
}
