
@echo off
@call "%VS110COMNTOOLS%\VsDevCmd.bat"

cd build_host
cmake "-GNMake Makefiles"  ..
nmake
cd ..
