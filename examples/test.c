/**
 * Copyright (c) Project Iota
 *
 * uCbor is licensed under an Apache license, version 2.0 license.
 * All rights not explicitly granted in the Apache license, version 2.0 are reserved.
 * See the included LICENSE file for more details.
 */
#include <stdio.h>
#include "erpc.h"


const char *req =
	"{\"method\": \"digitalWrite\", "
	"\"params\": [\"users\", \"wheel\", \"audio\", \"video\"], \"rto\": \"/user/1234/out\"}";


void digitalWrite(int argc, char *argv[])
{
    printf("FNC: digitalWrite()\n");
}

void digitalRead(int argc, char *argv[])
{
    printf("FNC: digitalRead()\n");
}


int main ()
{
    printf("Hello test!\n");


    /** Initialize it with our functions */
    erpcAddFunction("digitalWrite", digitalWrite);
    erpcAddFunction("digitalRead", digitalRead);

    /** Now we can call the function */
    erpcCall(req);

    return 0;
}
