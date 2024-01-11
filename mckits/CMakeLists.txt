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
  platform/mckits_mfile.h
  platform/mckits_mos.h
  platform/mckits_thread.h
  core/mckits_adt_flowqueue.h
  core/mckits_adt_hashmap.h
  core/mckits_adt_heap.h
  core/mckits_adt_list.h
  core/mckits_adt_mpmcqueue.h
  core/mckits_adt_nlist.h
  core/mckits_adt_rbtree.h
  core/mckits_adt_ring.h
  core/mckits_adt_skiplist.h
  core/mckits_array.h
  core/mckits_crc.h
  core/mckits_encoding_base32.h
  core/mckits_encoding_base64.h
  core/mckits_encoding_binary.h
  core/mckits_encoding_hex.h
  core/mckits_encoding_iniparser.h
  core/mckits_encoding_json.h
  core/mckits_encoding_toml.h
  core/mckits_endian.h
  core/mckits_hash_fnv.h
  core/mckits_hash_murmur.h
  core/mckits_mlog.h
  core/mckits_mrandom.h
  core/mckits_msock.h
  core/mckits_mtime.h
  core/mckits_rawpipe.h
  core/mckits_strconv.h
  core/mckits_string.h
  core/mckits_utils.h
)

set(mckits_srcs
  mckits.c
  platform/mckits_mfile.c
  platform/mckits_mos.c
  platform/mckits_thread.c
  core/mckits_adt_flowqueue.c
  core/mckits_adt_hashmap.c
  core/mckits_adt_heap.c
  core/mckits_adt_list.c
  core/mckits_adt_mpmcqueue.c
  core/mckits_adt_nlist.c
  core/mckits_adt_rbtree.c
  core/mckits_adt_ring.c
  core/mckits_adt_skiplist.c
  core/mckits_array.c
  core/mckits_encoding_base32.c
  core/mckits_encoding_base64.c
  core/mckits_encoding_binary.c
  core/mckits_encoding_hex.c
  core/mckits_encoding_iniparser.c
  core/mckits_encoding_json.c
  core/mckits_encoding_toml.c
  core/mckits_endian.c
  core/mckits_hash_fnv.c
  core/mckits_hash_murmur.c
  core/mckits_mlog.c
  core/mckits_mrandom.c
  core/mckits_msock.c
  core/mckits_mtime.c
  core/mckits_rawpipe.c
  core/mckits_strconv.c
  core/mckits_string.c
  core/mckits_utils.c
)

# set(mckits_libs ${mckits_libs} pthread)
set(mckits_libs ${mckits_libs} m)
set(mckits_libs ${mckits_libs} dl)
set(mckits_libs ${mckits_libs} rt)

if(BUILD_SHARED)
  add_library(mckits SHARED ${mckits_srcs})
  target_include_directories(mckits PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/platform
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
    ${PROJECT_SOURCE_DIR}/core
    ${PROJECT_SOURCE_DIR}/platform
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
