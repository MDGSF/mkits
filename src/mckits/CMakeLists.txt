project(mckits VERSION 0.0.1)

set(MCKITS_INCLUDE_HOME "${SOLUTION_INCLUDE_HOME}/mckits")
set(MCKITS_SRC_HOME "${SOLUTION_SRC_HOME}/mckits")

message(STATUS "[mckits] CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "[mckits] BUILD_SHARED: ${BUILD_SHARED}")
message(STATUS "[mckits] BUILD_STATIC: ${BUILD_STATIC}")
message(STATUS "[mckits] MCKITS_INCLUDE_HOME: ${MCKITS_INCLUDE_HOME}")
message(STATUS "[mckits] MCKITS_SRC_HOME: ${MCKITS_SRC_HOME}")

set(mckits_mlibc_headers
  ${MCKITS_INCLUDE_HOME}/mlibc/mckits_config.h
  ${MCKITS_INCLUDE_HOME}/mlibc/mckits_cwrap.h
  ${MCKITS_INCLUDE_HOME}/mlibc/mckits_malloc.h
  ${MCKITS_INCLUDE_HOME}/mlibc/mckits_mlibc_utils.h
)

set(mckits_mlibc_srcs
  ${MCKITS_SRC_HOME}/mlibc/mckits_cwrap.c
  ${MCKITS_SRC_HOME}/mlibc/mckits_malloc.c
  ${MCKITS_SRC_HOME}/mlibc/mckits_mlibc_utils.c
)

set(mckits_mstl_encoding_headers
  ${MCKITS_INCLUDE_HOME}/mstl/encoding/mckits_encoding_base32.h
  ${MCKITS_INCLUDE_HOME}/mstl/encoding/mckits_encoding_base64.h
  ${MCKITS_INCLUDE_HOME}/mstl/encoding/mckits_encoding_binary.h
  ${MCKITS_INCLUDE_HOME}/mstl/encoding/mckits_encoding_hex.h
)

set(mckits_mstl_encoding_srcs
  ${MCKITS_SRC_HOME}/mstl/encoding/mckits_encoding_base32.c
  ${MCKITS_SRC_HOME}/mstl/encoding/mckits_encoding_base64.c
  ${MCKITS_SRC_HOME}/mstl/encoding/mckits_encoding_binary.c
  ${MCKITS_SRC_HOME}/mstl/encoding/mckits_encoding_hex.c
)

set(mckits_mstl_hash_headers
  ${MCKITS_INCLUDE_HOME}/mstl/hash/mckits_crc.h
  ${MCKITS_INCLUDE_HOME}/mstl/hash/mckits_hash_fnv.h
  ${MCKITS_INCLUDE_HOME}/mstl/hash/mckits_hash_murmur.h
  ${MCKITS_INCLUDE_HOME}/mstl/hash/mckits_hash_sip.h
  ${MCKITS_INCLUDE_HOME}/mstl/hash/mckits_hash_xxhash.h
)

set(mckits_mstl_hash_srcs
  ${MCKITS_SRC_HOME}/mstl/hash/mckits_hash_fnv.c
  ${MCKITS_SRC_HOME}/mstl/hash/mckits_hash_murmur.c
  ${MCKITS_SRC_HOME}/mstl/hash/mckits_hash_sip.c
  ${MCKITS_SRC_HOME}/mstl/hash/mckits_hash_xxhash.c
)

set(mckits_mstl_headers
  ${mckits_mstl_encoding_headers}
  ${mckits_mstl_hash_headers}
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_hashmap.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_hashset.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_heap.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_list.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_nlist.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_rbtree.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_ring.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_skiplist.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_array.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_string.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_vecdeque.h
  ${MCKITS_INCLUDE_HOME}/mstl/mckits_vector.h
)

set(mckits_mstl_srcs
  ${mckits_mstl_encoding_srcs}
  ${mckits_mstl_hash_srcs}
  ${MCKITS_SRC_HOME}/mstl/mckits_hashmap.c
  ${MCKITS_SRC_HOME}/mstl/mckits_hashset.c
  ${MCKITS_SRC_HOME}/mstl/mckits_heap.c
  ${MCKITS_SRC_HOME}/mstl/mckits_list.c
  ${MCKITS_SRC_HOME}/mstl/mckits_nlist.c
  ${MCKITS_SRC_HOME}/mstl/mckits_rbtree.c
  ${MCKITS_SRC_HOME}/mstl/mckits_ring.c
  ${MCKITS_SRC_HOME}/mstl/mckits_skiplist.c
  ${MCKITS_SRC_HOME}/mstl/mckits_array.c
  ${MCKITS_SRC_HOME}/mstl/mckits_string.c
  ${MCKITS_SRC_HOME}/mstl/mckits_vecdeque.c
  ${MCKITS_SRC_HOME}/mstl/mckits_vector.c
)

set(mckits_core_encoding_headers
  ${MCKITS_INCLUDE_HOME}/core/encoding/mckits_encoding_iniparser.h
  ${MCKITS_INCLUDE_HOME}/core/encoding/mckits_encoding_json.h
  ${MCKITS_INCLUDE_HOME}/core/encoding/mckits_encoding_toml.h
  ${MCKITS_INCLUDE_HOME}/core/encoding/mckits_endian.h
)

set(mckits_core_encoding_srcs
  ${MCKITS_SRC_HOME}/core/encoding/mckits_encoding_iniparser.c
  ${MCKITS_SRC_HOME}/core/encoding/mckits_encoding_json.c
  ${MCKITS_SRC_HOME}/core/encoding/mckits_encoding_toml.c
  ${MCKITS_SRC_HOME}/core/encoding/mckits_endian.c
)

set(mckits_core_queue_headers
  ${MCKITS_INCLUDE_HOME}/core/queue/mckits_adt_flowqueue.h
  ${MCKITS_INCLUDE_HOME}/core/queue/mckits_adt_mpmcqueue.h
)

set(mckits_core_queue_srcs
  ${MCKITS_SRC_HOME}/core/queue/mckits_adt_flowqueue.c
  ${MCKITS_SRC_HOME}/core/queue/mckits_adt_mpmcqueue.c
)

set(mckits_core_thread_headers
  ${MCKITS_INCLUDE_HOME}/core/thread/mckits_atomic.h
  ${MCKITS_INCLUDE_HOME}/core/thread/mckits_rwlock.h
  ${MCKITS_INCLUDE_HOME}/core/thread/mckits_rwlockp.h
  ${MCKITS_INCLUDE_HOME}/core/thread/mckits_spinlock.h
)

set(mckits_core_headers
  ${mckits_core_encoding_headers}
  ${mckits_core_queue_headers}
  ${mckits_core_thread_headers}
  ${MCKITS_INCLUDE_HOME}/core/mckits_core_utils.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_daemon.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_mfile.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_mlog.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_mrandom.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_mtime.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_mos.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_msock.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_rawpipe.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_socket_poller.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_strconv.h
  ${MCKITS_INCLUDE_HOME}/core/mckits_thread.h
)

set(mckits_core_srcs
  ${mckits_core_encoding_srcs}
  ${mckits_core_queue_srcs}
  ${MCKITS_SRC_HOME}/core/mckits_core_utils.c
  ${MCKITS_SRC_HOME}/core/mckits_daemon.c
  ${MCKITS_SRC_HOME}/core/mckits_mfile.c
  ${MCKITS_SRC_HOME}/core/mckits_mlog.c
  ${MCKITS_SRC_HOME}/core/mckits_mrandom.c
  ${MCKITS_SRC_HOME}/core/mckits_mtime.c
  ${MCKITS_SRC_HOME}/core/mckits_mos.c
  ${MCKITS_SRC_HOME}/core/mckits_msock.c
  ${MCKITS_SRC_HOME}/core/mckits_rawpipe.c
  ${MCKITS_SRC_HOME}/core/mckits_socket_poller.c
  ${MCKITS_SRC_HOME}/core/mckits_strconv.c
  ${MCKITS_SRC_HOME}/core/mckits_thread.c
)

if(WIN32)
  set(mckits_headers
    ${mckits_mlibc_headers}
    ${mckits_mstl_headers}
  )

  set(mckits_srcs
    ${mckits_mlibc_srcs}
    ${mckits_mstl_srcs}
  )
endif()

if(UNIX)
  set(mckits_headers
    ${MCKITS_INCLUDE_HOME}/mckits.h
    ${mckits_mlibc_headers}
    ${mckits_mstl_headers}
    ${mckits_core_headers}
  )

  set(mckits_srcs
    ${MCKITS_SRC_HOME}/mckits.c
    ${mckits_mlibc_srcs}
    ${mckits_mstl_srcs}
    ${mckits_core_srcs}
  )
endif()

if(BUILD_SHARED)
  add_library(mckits SHARED ${mckits_srcs})
  target_include_directories(mckits PUBLIC
    ${SOLUTION_INCLUDE_HOME}
    ${SOLUTION_HOME}
  )
  target_link_libraries(mckits ${mckits_libs})
  target_compile_options(mckits PRIVATE ${mckits_compile_options})
  target_link_options(mckits PRIVATE ${mckits_link_options})
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
    ${SOLUTION_INCLUDE_HOME}
    ${SOLUTION_HOME}
  )
  target_link_libraries(mckits_static ${mckits_libs})
  target_compile_options(mckits_static PRIVATE ${mckits_compile_options})
  target_link_options(mckits_static PRIVATE ${mckits_link_options})
  install(TARGETS mckits_static
    ARCHIVE DESTINATION lib
  )
  add_custom_target(libmckits_static DEPENDS mckits_static)
endif()

install(DIRECTORY ${MCKITS_INCLUDE_HOME} DESTINATION include)
