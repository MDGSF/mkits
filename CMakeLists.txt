cmake_minimum_required(VERSION 3.13.1)

project(mkits)

option(BUILD_SHARED "build shared library" ON)
option(BUILD_STATIC "build static library" ON)

option(BUILD_MCKITS "build mckits" ON)
option(BUILD_MCPPKITS "build mcppkits" ON)
option(BUILD_UNITTEST "build unittest" OFF)
option(BUILD_BENCH "build bench" OFF)

message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  add_definitions(-DDEBUG)
else()
  add_definitions(-DNDEBUG)
endif()

if(BUILD_MCKITS)
  add_subdirectory(mckits)
endif()

if(BUILD_MCPPKITS)
  add_subdirectory(mcppkits)
endif()

if(BUILD_UNITTEST)
  enable_testing()
  add_subdirectory(test/mckits)
endif()

if(BUILD_BENCH)
  add_subdirectory(bench/mckits)
endif()

