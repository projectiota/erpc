## Jsmnrpc
Minimal JSON RPC library based on [Jsmn](https://github.com/zserge/jsmn).

It has no dependencies and fits in one C file, suitable for embbeding in constrained devices.

## Install

### Build Library
```bash
# Clone the repo
git clone https://github.com/projectiota/jsmnrpc && cd jsmnrpc
make
```
Static library `libjsmnrpc.a` will be created.

### Build Example and Test
```bash
make test
./test
```

## License
[Apache-2.0](LICENSE)
