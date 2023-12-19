project(mckits)

set(CMAKE_C_FLAGS_DEBUG   "-std=c11 -Wall -g")
set(CMAKE_C_FLAGS_RELEASE "-std=c11 -Wall -O3")

add_library(mckits SHARED
  mckits.c
)
