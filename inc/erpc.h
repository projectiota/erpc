/**
 * Copyright (c) Project Iota
 *
 * uCbor is licensed under an Apache license, version 2.0 license.
 * All rights not explicitly granted in the Apache license, version 2.0 are reserved.
 * See the included LICENSE file for more details.
 */

#ifndef ERPC_H
#define ERPC_H

int erpcCall(const char* req, char* rsp);

void erpcSetFncTable( void (*(*ft)[])(int argc, char *argv[]) );

#endif /** ERPC_H */

