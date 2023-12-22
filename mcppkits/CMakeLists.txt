project(mcppkits VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -Wall -O3")

set(mcppkits_headers
  mcppkits.h
  mcppkits_dbgutils.h
  mcppkits_fps.h
  mcppkits_strutils.h
)

set(mcppkits_srcs
  mcppkits.cpp
  mcppkits_strutils.cpp
)

set(mckits_libs ${mckits_libs} m)
set(mckits_libs ${mckits_libs} dl)
set(mckits_libs ${mckits_libs} rt)
set(mckits_libs ${mckits_libs} stdc++)

if(BUILD_SHARED)
  add_library(mcppkits SHARED ${mcppkits_srcs})
  target_include_directories(mcppkits PUBLIC
    ${PROJECT_SOURCE_DIR}
  )
  target_link_libraries(mcppkits ${mckits_libs})
  target_compile_options(mcppkits PRIVATE -pthread)
  target_link_options(mcppkits PRIVATE -pthread)
  install(TARGETS mcppkits
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
  )
  add_custom_target(libmcppkits DEPENDS mcppkits)
endif()

if(BUILD_STATIC)
  add_library(mcppkits_static STATIC ${mcppkits_srcs})
  target_include_directories(mcppkits_static PUBLIC
    ${PROJECT_SOURCE_DIR}
  )
  target_link_libraries(mcppkits_static ${mckits_libs})
  target_compile_options(mcppkits_static PRIVATE -pthread)
  target_link_options(mcppkits_static PRIVATE -pthread)
  install(TARGETS mcppkits_static
    ARCHIVE DESTINATION lib
  )
  add_custom_target(libmcppkits_static DEPENDS mcppkits_static)
endif()

install(FILES ${mcppkits_headers} DESTINATION include/mcppkits)

