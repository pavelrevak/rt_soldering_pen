# RT soldering pen

## Building and flashing

### Requirements

- [cmake](https://cmake.org/download/)
- [arm-gcc](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
- `make` or [ninja](https://github.com/ninja-build/ninja)
- STM flashing SW and hardware (ST-Link/V2 or any ST dev-kit, like Discovery or Nucleo board)

Building is possible on Linux, Mac and also on Windows

### Getting source

```bash
git clone https://github.com/pavelrevak/rt_soldering_pen.git
git submodule update --recursive
```

### Building

```bash
mkdir _build
cd _build
cmake -D CMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi.cmake -D CMAKE_BUILD_TYPE=Release ..
make
```

### Flashing

If you have installed [pystlink](https://github.com/pavelrevak/pystlink) and is in search path with ST-Link/V2 programing tool:

```bash
make flash
```

If you have another flashing utility you can generate hex of binary file:

```bash
make srec
```

or building also support other targets `hex` and `bin`

Final files you can find in `_build` folder
