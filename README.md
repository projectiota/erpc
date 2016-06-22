## Jsmnrpc
Minimal JSON RPC library based on [Jsmn](https://github.com/zserge/jsmn).

It has no dependencies and fits in one C file, suitable for embbeding in constrained devices.

## Install

### Prepare the Jsmn Dependency
Jsmnrpc depends on [Jsmn](https://github.com/zserge/jsmn). Static `libjsmn.a` as well as `jsmn.h` header file are needed for building of `libjsmnrpc.a`.

However, we do not include Jsmn code in Jsmnrpc repo (not even as a submodule) as many embedded build system have it already - like [RIOT](https://github.com/RIOT-OS/RIOT/tree/master/pkg/jsmn) or [esp-open-rtos](https://github.com/SuperHouse/esp-open-rtos/tree/master/extras/jsmn) for example.

In the case that you are buiding Jsmnrpc independantly and out of the build system which has Jsmn installed (for example if you just cloned this repo to your PC), you will have to fetch and build Jsmn by hand.

Good news is that this is really simple:
```bash
git clone https://github.com/zserge/jsmn
make -C ./jsmn
```
Now you are ready to build Jsmnrpc library.

### Build Library
```bash
# Clone the repo
git clone https://github.com/projectiota/jsmnrpc && cd jsmnrpc
```
By default, our [Makefile](Makefile) considers that you placed `jsmn` directory next to the `jsmnrpc` directory (on the same level). In this case, you can type just:

```bash
make
```
Otherwise, you have to tell the `GNU Make` where to look for `jsmn` files:
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
