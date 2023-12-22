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
  mckits_mfile.h
  mckits_mlog.h
  mckits_mos.h
  mckits_mrandom.h
  mckits_msock.h
  mckits_mtime.h
  mckits_thread.h
  mckits_utils.h
)

set(mckits_srcs
  mckits.c
  mckits_encoding_binary.c
  mckits_mfile.c
  mckits_mlog.c
  mckits_mos.c
  mckits_mrandom.c
  mckits_msock.c
  mckits_mtime.c
  mckits_rawpipe.c
  mckits_thread.c
  mckits_utils.c
)

# set(mckits_libs ${mckits_libs} pthread)
set(mckits_libs ${mckits_libs} m)
set(mckits_libs ${mckits_libs} dl)
set(mckits_libs ${mckits_libs} rt)

if(BUILD_SHARED)
  add_library(mckits SHARED ${mckits_srcs})
  target_include_directories(mckits PUBLIC
    ${PROJECT_SOURCE_DIR}
  )
  target_link_libraries(mckits ${mckits_libs})
  target_compile_options(mckits PRIVATE -pthread)
  target_link_options(mckits PRIVATE -pthread)
  install(TARGETS mckits
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
  )
  add_custom_target(libmckits DEPENDS mckits)
endif()

if(BUILD_STATIC)
  add_library(mckits_static STATIC ${mckits_srcs})
  target_include_directories(mckits_static PUBLIC
    ${PROJECT_SOURCE_DIR}
  )
  target_link_libraries(mckits_static ${mckits_libs})
  target_compile_options(mckits_static PRIVATE -pthread)
  target_link_options(mckits_static PRIVATE -pthread)
  install(TARGETS mckits_static
    ARCHIVE DESTINATION lib
  )
  add_custom_target(libmckits_static DEPENDS mckits_static)
endif()

install(FILES ${mckits_headers} DESTINATION include/mckits)

