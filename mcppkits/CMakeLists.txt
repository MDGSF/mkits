project(mcppkits)

set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -Wall -O3")

set(mcppkits_headers
  mcppkits.h
)

set(mcppkits_srcs
  mcppkits.cpp
)

if(BUILD_SHARED)
  add_library(mcppkits SHARED ${mcppkits_srcs})
  target_include_directories(mcppkits PUBLIC
    ${PROJECT_SOURCE_DIR}
  )
  install(TARGETS mcppkits
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
  )
endif()

if(BUILD_STATIC)
  add_library(mcppkits_static STATIC ${mcppkits_srcs})
  target_include_directories(mcppkits_static PUBLIC
    ${PROJECT_SOURCE_DIR}
  )
  install(TARGETS mcppkits_static
    ARCHIVE DESTINATION lib
  )
endif()

install(FILES ${mcppkits_headers} DESTINATION include/mcppkits)

