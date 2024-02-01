#!/usr/bin/env bash

echo "Start cpplint Code..."

SCRIPT_HOME=$(cd `dirname $0` && pwd)
SOLUTION_HOME=$SCRIPT_HOME
BUILD_HOME=$SOLUTION_HOME/build
MCKITS_HOME=$SOLUTION_HOME/mckits
MCPPKITS_HOME=$SOLUTION_HOME/mcppkits

# cpplint -h 查看帮助文档
# cpplint --recursive dir1 dir2 dir3 ...
cpplint \
  --recursive \
  $MCPPKITS_HOME
