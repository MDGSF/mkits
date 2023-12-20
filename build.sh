#!/usr/bin/env bash

SCRIPT_HOME=$(cd `dirname $0` && pwd)
compile="Release"
#compile="Debug"

echo "SCRIPT_HOME = $SCRIPT_HOME"

mkdir -p build
cd build

cmake \
  -DCMAKE_BUILD_TYPE=$compile \
  -DCMAKE_INSTALL_PREFIX=output \
  -DBUILD_UNITTEST=ON \
  -DBUILD_BENCH=ON \
  ..

make
# make VERBOSE=1
make install
