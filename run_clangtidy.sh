#!/usr/bin/env bash

echo "Start clang-tidy Code..."

SCRIPT_HOME=$(cd `dirname $0` && pwd)
SOLUTION_HOME=$SCRIPT_HOME
BUILD_HOME=$SOLUTION_HOME/build
SOLUTION_INCLUDE_HOME=$SOLUTION_HOME/include
SOLUTION_SRC_HOME=$SOLUTION_HOME/src
MCKITS_INCLUDE_HOME=$SOLUTION_INCLUDE_HOME/mckits
MCKITS_SRC_HOME=$SOLUTION_SRC_HOME/mckits
MCPPKITS_INCLUDE_HOME=$SOLUTION_INCLUDE_HOME/mcppkits
MCPPKITS_SRC_HOME=$SOLUTION_SRC_HOME/mcppkits

# run-clang-tidy.py -h 查看帮助文档
$SOLUTION_HOME/run-clang-tidy.py \
  -config-file $SOLUTION_HOME/.clang-tidy \
  -p build \
  $SOLUTION_INCLUDE_HOME \
  $SOLUTION_SRC_HOME
