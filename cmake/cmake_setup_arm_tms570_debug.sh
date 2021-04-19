#!/bin/sh
source_dir=$(cd ../ && pwd)

counter=0
if [ -z "$RTEMS_PREFIX" ]; then
	echo "RTEMS_PREFIX environmental variable (RTEMS prefix) has to be set!"
	exit 1
fi

if [ -z "$RTEMS_VERSION" ]; then
	echo "RTEMS_VERSION environmental variable not set. Will be autodetermined from tools path"
fi

while [ ${counter} -lt 5 ]
do
	cd ..
	if [ -d "rtems-cmake" ];then
		break
	fi
	counter=$((counter=counter + 1))
done

if [ "${counter}" -ge 5 ];then
	echo "create_cmake_cfg.sh not found in upper directories!"
	exit 1
fi

cd rtems-cmake

builddir="build-Debug"
build_generator=""
if [ "${OS}" = "Windows_NT" ]; then
	build_generator="MinGW Makefiles"
# Could be other OS but this works for now.
else
	build_generator="Unix Makefiles"
fi

echo "Running command (without the leading +):"
set -x # Print command 
python3 cmake_build_config.py -p "${RTEMS_PREFIX}" -t "arm/tms570ls3137_hdk" -g "${build_generator}" \
        -b "debug" -s "${source_dir}" -l "${builddir}"
# Use this if commands are added which should not be printed
# set +x
