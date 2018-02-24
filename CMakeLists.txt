cmake_minimum_required(VERSION 3.0)

# project name
project(rt-soldering-pen)

# path to io
set(IO_DIR "..")

# select linker script
set(LINKER_SCRIPT ${IO_DIR}/io/ld/stm32/f0/3xx6.ld)

# define CPU OPTIONS
set(CPU_OPTIONS -mthumb -mcpu=cortex-m0)

# optimizations (-O0 -O1 -O2 -O3 -Os -Ofast -Og -flto)
set(CMAKE_C_FLAGS_DEBUG "-Og -g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_C_FLAGS_RELEASE "-Os -flto")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto")

add_compile_options(
    ${CPU_OPTIONS}
    $<$<COMPILE_LANGUAGE:C>:-std=c11>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++14>
    $<$<COMPILE_LANGUAGE:CXX>:-fms-extensions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
    -Wall
    -pedantic
    -Wextra
    -fstrict-volatile-bitfields
    -ffunction-sections
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    src
    ${IO_DIR}
)

link_directories(
    ${CMAKE_SOURCE_DIR}
    src
    ${IO_DIR}
)

# list of modules to build final firmware (without extension .c or .cpp)
add_executable(${PROJECT_NAME}
    ${IO_DIR}/io/handlers/stack
    ${IO_DIR}/io/handlers/cortexm
    ${IO_DIR}/io/handlers/stm32/f0
    ${IO_DIR}/io/startup/stm32/f0
    src/pure_virtual_stub
    src/lib/font
    src/lib/str
    src/board/hardfault
    src/board/clock
    src/board/systick
    src/board/buttons
    src/board/heater
    src/board/debug
    src/board/adc
    src/board/i2c
    src/board/display
    src/main
)

target_link_libraries(${PROJECT_NAME}
    ${CPU_OPTIONS}
    -T${LINKER_SCRIPT}
    -nostartfiles
    # -nostdlib
)

set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_DEPENDS ${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT})

include("cmake/flash.cmake")
