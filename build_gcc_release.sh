#!/usr/bin/env bash

SCRIPT_HOME=$(cd `dirname $0` && pwd)
compile="Release"

echo "SCRIPT_HOME = $SCRIPT_HOME"

mkdir -p build
cd build

cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=output \
  -DBUILD_UNITTEST=OFF \
  -DBUILD_BENCH=ON \
  ..

make
# make VERBOSE=1
make install
