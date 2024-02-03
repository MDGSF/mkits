#!/usr/bin/env bash

SCRIPT_HOME=$(cd `dirname $0` && pwd)
PROJECT_HOME=$SCRIPT_HOME
SOLUTION_HOME=$SCRIPT_HOME
echo "SCRIPT_HOME = $SCRIPT_HOME"
echo "PROJECT_HOME = $PROJECT_HOME"
echo "SOLUTION_HOME = $SOLUTION_HOME"

mkdir -p build
cd build

cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_INSTALL_PREFIX=output \
  -DBUILD_UNITTEST=OFF \
  -DBUILD_BENCH=ON \
  -DSOLUTION_HOME=$SOLUTION_HOME \
  ..

make
# make VERBOSE=1
make install
