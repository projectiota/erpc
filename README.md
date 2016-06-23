## Jsmnrpc
Minimal JSON RPC library based on [Jsmn](https://github.com/zserge/jsmn).

It has no other dependencies than Jsmn and fits in one C file, suitable for embbeding in constrained devices.

## Install
### TL;DR
```bash
# Clone the repo
git clone --recursive https://github.com/projectiota/jsmnrpc && cd jsmnrpc
```

### Jsmn Dependency
Jsmnrpc depends on [Jsmn](https://github.com/zserge/jsmn). Jsmn code is included in Jsmnrpc repo via git submodule, so that the code can be fetched via `git submodule init && git submodule update`, or git recursive clone.

However, many embedded build system have Jsmn already included - like [RIOT](https://github.com/RIOT-OS/RIOT/tree/master/pkg/jsmn) or [esp-open-rtos](https://github.com/SuperHouse/esp-open-rtos/tree/master/extras/jsmn) for example. In that case you can tell the `GNU Make` where to look for `jsmn` source files:

```bash
make JSMNDIR=<path_to_jsmn>
```

Static library `libjsmnrpc.a` will be created.

### Build Example and Test
```bash
make test
./test
```

## License
[Apache-2.0](LICENSE)
