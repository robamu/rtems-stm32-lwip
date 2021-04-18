RTEMS lwIP STM32 Repository
======

This repository tests the new RTEMS lwIP support for the `arm/nucleo-h743zi` BSP.

# Building the application

It is assumed the RTEMS BSP is installed at the `RTEMS_PREFIX` location. On Windows, it
is recommended to install MinGW64 to have a Unix environment

## CMake

The application can be built with the following commands. On Windows, add `-G "MinGW Makefiles"` 
in the `CMake` build generation command before the `..`

```sh
git clone https://github.com/rmspacefish/rtems-stm32-lwip.git
cd rtems-stm32-lwip
mkdir build-Debug && cd build-Debug
cmake -DCMAKE_BUILD_TYPE="Debug" -DRTEMS_BSP="arm/nucleo-h743zi" -DRTEMS_PREFIX=$RTEMS_PREFIX ..
cmake --build . -j
```
# Prerequisites

See [here](https://github.com/rmspacefish/rtems-tools) for a guide to build the RTEMS BSP.
Alternatively, you can download pre-compiled BSPs for Windows from
[here](https://drive.google.com/drive/u/0/folders/15pO3FCUwceghrnYjmNlgC6K1Z8D_6iu2)

# Flashing the application

You can flash the application with Drag & Drop or with OpenOCD. An Eclipse project file is provided
to get started with OpenOCD. You can install OpenOCD for Windows from [here](https://xpack.github.io/openocd/)
with `xpm` to have good Eclipse integration.
