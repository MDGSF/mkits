#!/usr/bin/env bash

SCRIPT_HOME=$(cd `dirname $0` && pwd)
PROJECT_HOME=$SCRIPT_HOME
echo "SCRIPT_HOME = $SCRIPT_HOME"

mkdir -p build
cd build

cmake \
  -DCMAKE_C_COMPILER=clang \
  -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_USER_MAKE_RULES_OVERRIDE=$PROJECT_HOME/scripts/ClangOverrides.txt \
  -D_CMAKE_TOOLCHAIN_PREFIX=llvm- \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
  -DCMAKE_INSTALL_PREFIX=output \
  -DBUILD_UNITTEST=ON \
  -DBUILD_BENCH=ON \
  ..

make -j 8
#make VERBOSE=1
make install

ctest
