# RT soldering pen

![oled4]

[Manual]

This firmware is for my project [RT soldering pen](https://hackaday.io/project/18899-rt-soldering-pen)

You can buy HW at [Tindie](https://www.tindie.com/products/vlk/rt-soldering-pen/)

## Building and flashing

### Requirements

- [`arm-gcc`](https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads)
- [`cmake`](https://cmake.org/download/)
- `make` or [`ninja`](https://github.com/ninja-build/ninja)
- STM flashing SW and HW (ST-Link/V2 or any ST dev-kit, like Discovery or Nucleo board)

Building is possible on Linux, Mac and also on Windows

### Getting source

```sh
git clone --recursive https://github.com/pavelrevak/rt_soldering_pen.git
cd rt_soldering_pen
```

### Building

```sh
mkdir _build
cd _build
cmake -D CMAKE_TOOLCHAIN_FILE=../cmake/arm-none-eabi.cmake -D CMAKE_BUILD_TYPE=Release ..
make
```

### Flashing

Connect ST-Link or other SWD programmer:

#### HW v0.3

- G : GND
- C : SWCLK
- D : SWDIO

#### HW v1.0

- C : SWCLK
- G : GND
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

Final files are saved in `_build` folder

[manual]: doc/MANUAL.md "Manual"
[oled4]: doc/oled4.png "Screenshot"
