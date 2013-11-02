#!/bin/bash
#
echo
echo " *** Build for host test code"
echo
if [[ ! -d build_host ]];
then
  mkdir build_host
fi
( cd build_host && cmake ../ && make all && ctest --output-on-failure ) || exit

echo
echo " *** Build for Arduino Target"
echo
if [[ ! -d build_target ]];
then
  mkdir build_target
fi
( cd build_target \
    && cmake -DBOARDPORT=/dev/tty.usbmodem621 -DCMAKE_TOOLCHAIN_FILE=../arduino-cmake/cmake/ArduinoToolchain.cmake ../ \
    && make $* )

