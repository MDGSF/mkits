#!/usr/bin/env bash

echo "Start cppcheck Code..."

SCRIPT_HOME=$(cd `dirname $0` && pwd)
SOLUTION_HOME=$SCRIPT_HOME
BUILD_HOME=$SOLUTION_HOME/build
SOLUTION_INCLUDE_HOME=$SOLUTION_HOME/include
SOLUTION_SRC_HOME=$SOLUTION_HOME/src
MCKITS_INCLUDE_HOME=$SOLUTION_INCLUDE_HOME/mckits
MCKITS_SRC_HOME=$SOLUTION_SRC_HOME/mckits
MCPPKITS_INCLUDE_HOME=$SOLUTION_INCLUDE_HOME/mcppkits
MCPPKITS_SRC_HOME=$SOLUTION_SRC_HOME/mcppkits

# 将mckits和mcppkits的每个子目录作为参数添加到cppcheck的-I参数后面
mkits_cppcheck_args=()

while IFS= read -r -d '' subdir; do
  mkits_cppcheck_args+=("-I$subdir")
done < <(find "$MCKITS_SRC_HOME" -type d -print0)

while IFS= read -r -d '' subdir; do
  mkits_cppcheck_args+=("-I$subdir")
done < <(find "$MCPPKITS_SRC_HOME" -type d -print0)

echo "${mkits_cppcheck_args[@]}"

# cppcheck -h 查看帮助文档
cppcheck \
  --project=$BUILD_HOME/compile_commands.json \
  -i ${SOLUTION_HOME}/build \
  -i ${SOLUTION_HOME}/scripts \
  -I${SOLUTION_INCLUDE_HOME} \
  ${mkits_cppcheck_args[@]} \
  ${SOLUTION_HOME} \
  2> cppcheck_err.txt

exit_code="$?"
echo "cppcheck Code Finished. $exit_code"
exit $exit_code
