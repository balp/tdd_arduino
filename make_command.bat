
rem @echo off
@call "%VS110COMNTOOLS%\VsDevCmd.bat"

rmdir /s /q build_host
mkdir build_host
cd build_host
cmake "-GNMake Makefiles"  ..
nmake
cd ..

rmdir /s /q build_vs
mkdir build_vs
cd build_vs
cmake ..
cd ..

rem set ARDUINO_SDK_PATH="c:\Program Files (x86)\Arduino\"
rem set PATH=%ARDUINO_SDK_PATH%\hardware\tools\avr\utils\bin;C:\Program Files (x86)\Arduino\hardware\tools\avr\bin;%PATH%

rmdir /s /q build_target
mkdir build_target
cd build_target
cmake "-GNMake Makefiles"  -DCMAKE_TOOLCHAIN_FILE=..\arduino-cmake\cmake\ArduinoToolchain.cmake ..
nmake
cd ..
rem PAUSE

