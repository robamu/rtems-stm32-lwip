RTEMS lwIP STM32 Repository
======

This repository tests the new RTEMS lwIP support for the `arm/nucleo-h743zi` BSP.
After cloning this repository, make sure to clone the submodules as well

```sh
git submodule init
git submodule update
```

# Prerequisites

See [here](https://github.com/rmspacefish/rtems-tools) for a guide to build the RTEMS BSP.
Alternatively, you can download pre-compiled BSPs for Windows from
[here](https://drive.google.com/drive/u/0/folders/15pO3FCUwceghrnYjmNlgC6K1Z8D_6iu2)

# Configuring the application

The application can be configured by using the `conf_app.h` header file.

# Building the application

It is assumed the RTEMS BSP is installed at the `RTEMS_PREFIX` location. On Windows, it
is recommended to install [MinGW64](https://www.msys2.org/) to have a Unix environment and run the
following command to install `CMake` and required tools.

```sh
pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-toolchain
```

To connect to the STM32, make sure to install the `st-link` drivers 
from [here](https://github.com/stlink-org/stlink) as well.

## CMake

Set up the environmental variable `RTEMS_PREFIX` first

```sh
export RTEMS_PREFIX=<RTEMS Prefix Path>
```

You can also extract this step to a script which is `source`ed or add it to the environmental 
variables permanently by adding the line to the `.bashrc` file.

The application can be built with the following commands. On Windows, add `-G "MinGW Makefiles"` 
in the `CMake` build generation command before the `..`.

```sh
git clone https://github.com/rmspacefish/rtems-stm32-lwip.git
cd rtems-stm32-lwip
mkdir build-Debug && cd build-Debug
cmake -DCMAKE_BUILD_TYPE="Debug" -DRTEMS_BSP="arm/nucleo-h743zi" -DRTEMS_PREFIX=$RTEMS_PREFIX ..
cmake --build . -j
```

# Flashing the application

You can flash the application with Drag & Drop or with OpenOCD. An Eclipse project file is provided
to get started with OpenOCD. You can install OpenOCD for Windows from [here](https://xpack.github.io/openocd/)
with `xpm` to have good Eclipse integration.

# Testing the application

The `ip_client` contains a simply Python TCP/IP client implementation which can be
used to test the software.


# Using Eclipse

To use the given Eclipse project file, copy it from `eclipse` into the root. Then you can 
import the folder as an Eclipse project. Make sure to only import the root project file instead 
of both when importing the project. Right click on the project folder and go to C/C++ Build 
&rarr; Build Variables. Here you can set `RTEMS_PREFIX` accordingly to set up the Eclipse indexer.
