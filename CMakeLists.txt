CMAKE_MINIMUM_REQUIRED(VERSION 3.13.1)

project(mkits)

option(BUILD_SHARED "build shared library" ON)
option(BUILD_STATIC "build static library" ON)

option(BUILD_MCKITS "build mckits" ON)
option(BUILD_MCPPKITS "build mcppkits" ON)
option(BUILD_UNITTEST "build unittest" OFF)

if(BUILD_MCKITS)
  add_subdirectory(mckits)
endif()

if(BUILD_MCPPKITS)
  add_subdirectory(mcppkits)
endif()

if(BUILD_UNITTEST)
  add_subdirectory(test/mckits)
endif()
