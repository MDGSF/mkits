project(mcppkits)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -Wall -O3")

add_library(mcppkits SHARED
  mcppkits.cpp
)
