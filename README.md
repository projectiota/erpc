## Erpc
Minimal JSON RPC library based on [Jsmn](https://github.com/zserge/jsmn).

It has no other dependencies than Jsmn and fits in one C file, suitable for embbeding in constrained devices.

Being minimal, `erpc` has certain limitations:
- Method names are positive integers (we call these "function codes"). This is beacuse C implementation via function lookup table is simpler and faster then via hash functions (in case of method names as strings).
- No nested objects in parameters. This comes from Jsmn implementation, and it would be complicated to parse recursively.
- Instead of `id`, we use `rto`, or "reply to" field. This is because `erpc` expects specific MQTT topic over which response will be published to be passed for each request. Caller can then allocate MQTT topics with incrementing integers in name, and aggregate messages in order.

Erpc library was created for the needs of [Electrolink](https://github.com/projectiota/electrolink) protocol implementation, so many design decisions come from there.

However, `erpc` can be used as an independant library in various applications as mentioned limitations most often are not critical in lightweight embedded context.

## Install
### TL;DR
```bash
# Clone the repo
git clone --recursive https://github.com/projectiota/erpc && cd erpc
make
```
Static library `liberpc.a` will be created.

### Jsmn Dependency
Erpc depends on [Jsmn](https://github.com/zserge/jsmn). Jsmn code is included in Erpc repo via git submodule, so that the code can be fetched via `git submodule init && git submodule update`, or git recursive clone.

However, many embedded build system have Jsmn already included - like [RIOT](https://github.com/RIOT-OS/RIOT/tree/master/pkg/jsmn) or [esp-open-rtos](https://github.com/SuperHouse/esp-open-rtos/tree/master/extras/jsmn) for example. In that case you can tell the `GNU Make` where to look for `jsmn` source files:

```bash
make JSMNDIR=<path_to_jsmn>
```

### Build Example and Test
```bash
make test
./test
```
## Author
Erpc was engineered by [@drasko](https://github.com/drasko) for the needs of [Electrolink](https://github.com/projectiota/electrolink) project.

## License
[Apache-2.0](LICENSE)
