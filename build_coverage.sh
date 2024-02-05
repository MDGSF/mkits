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
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_INSTALL_PREFIX=output \
  -DBUILD_UNITTEST=ON \
  -DBUILD_BENCH=ON \
  -DBUILD_COVERAGE=ON \
  ..

make
# make VERBOSE=1
make install

ctest

lcov -c -o coverage.info -b . -d .
genhtml coverage.info -o coverage_report
