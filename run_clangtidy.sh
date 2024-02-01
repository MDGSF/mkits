#!/usr/bin/env bash

echo "Start clang-tidy Code..."

SCRIPT_HOME=$(cd `dirname $0` && pwd)
SOLUTION_HOME=$SCRIPT_HOME
BUILD_HOME=$SOLUTION_HOME/build
MCKITS_HOME=$SOLUTION_HOME/mckits
MCPPKITS_HOME=$SOLUTION_HOME/mcppkits

# run-clang-tidy.py -h 查看帮助文档
$SOLUTION_HOME/run-clang-tidy.py \
  -config-file $SOLUTION_HOME/.clang-tidy \
  -p build \
  $MCKITS_HOME \
  $MCPPKITS_HOME
