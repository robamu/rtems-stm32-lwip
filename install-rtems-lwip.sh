#!/bin/sh
cd build-Debug 
export LWIP_OPTS_PATH=$(pwd)
cd ..
export LWIP_OPTS_PATH="$LWIP_OPTS_PATH $(pwd)"
echo "lwIP options path: $LWIP_OPTS_PATH"

cd rtems-lwip

python3 waf configure --prefix=$RTEMS_PREFIX --rtems-bsp=arm/nucleo-h743zi \
    --lwip-opts="$LWIP_OPTS_PATH"
python3 waf
python3 waf install

