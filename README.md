# RT soldering pen

## Building and flashing

### Requirements

- [`arm-gcc`](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
- [`cmake`](https://cmake.org/download/)
- `make` or [`ninja`](https://github.com/ninja-build/ninja)
- STM flashing SW and HW (ST-Link/V2 or any ST dev-kit, like Discovery or Nucleo board)

Building is possible on Linux, Mac and also on Windows

### Getting source

```sh
git clone https://github.com/pavelrevak/rt_soldering_pen.git
cd rt_soldering_pen
git submodule update --recursive
```

### Building

```sh
mkdir _build
cd _build
cmake -D CMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi.cmake -D CMAKE_BUILD_TYPE=Release ..
make
```

### Flashing

Connect programmer:
- G : GND
- C : SWCLK
- D : SWDIO

If you have installed [pystlink](https://github.com/pavelrevak/pystlink) and is in search path just type:

```sh
make flash
```

If you have another flashing utility you can generate hex of binary file:

```sh
make srec
```

or building also support other targets `hex` and `bin`

Final files you can find in `_build` folder
