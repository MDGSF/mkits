#!/usr/bin/env bash

SCRIPT_HOME=$(cd `dirname $0` && pwd)
compile="Release"
#compile="Debug"

echo "SCRIPT_HOME = $SCRIPT_HOME"

mkdir -p build
cd build

cmake \
  -DCMAKE_SYSTEM_NAME=Linux \
  -DCMAKE_BUILD_TYPE=$compile \
  -DCMAKE_CXX_COMPILER=g++ \
  -DCMAKE_C_COMPILER=gcc \
  -DCMAKE_AR=ar \
  ..

make
# make VERBOSE=1
