project(mckits)

message(STATUS "[mckits] PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

set(CMAKE_C_FLAGS_DEBUG   "-std=c11 -Wall -g")
set(CMAKE_C_FLAGS_RELEASE "-std=c11 -Wall -O3")

add_library(mckits SHARED
  mckits.c
  mckits_encoding_binary.c
)

target_include_directories(mckits
  PUBLIC
  ${PROJECT_SOURCE_DIR}
)