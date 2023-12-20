project(mckits VERSION 0.0.1)

message(STATUS "[mckits] CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "[mckits] BUILD_SHARED: ${BUILD_SHARED}")
message(STATUS "[mckits] BUILD_STATIC: ${BUILD_STATIC}")
message(STATUS "[mckits] PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS_DEBUG "-std=c11 -Wall -g")
set(CMAKE_C_FLAGS_RELEASE "-std=c11 -Wall -O3")

set(mckits_headers
  mckits.h
  mckits_encoding_binary.h
)

set(mckits_srcs
  mckits.c
  mckits_encoding_binary.c
)

if(BUILD_SHARED)
  add_library(mckits SHARED ${mckits_srcs})
  target_include_directories(mckits PUBLIC
    ${PROJECT_SOURCE_DIR}
  )
  install(TARGETS mckits
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
  )
endif()

if(BUILD_STATIC)
  add_library(mckits_static STATIC ${mckits_srcs})
  target_include_directories(mckits_static PUBLIC
    ${PROJECT_SOURCE_DIR}
  )
  install(TARGETS mckits_static
    ARCHIVE DESTINATION lib
  )
endif()

install(FILES ${mckits_headers} DESTINATION include/mckits)

