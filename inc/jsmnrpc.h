/**
 * Copyright (c) Project Iota
 *
 * uCbor is licensed under an Apache license, version 2.0 license.
 * All rights not explicitly granted in the Apache license, version 2.0 are reserved.
 * See the included LICENSE file for more details.
 */

#ifndef JSMNRPC_H
#define JSMNRPC_H

int jrpcCall(const char* req, char* rsp);

void setFncTable( void (*(*ft)[])(int argc, char *argv[]) );

#endif /** JSMNRPC_H */

