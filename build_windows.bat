@echo off

cmake ^
  -S . ^
  -B build

cmake --build build --config Debug
REM cmake --build build --config Release

REM ctest

pause