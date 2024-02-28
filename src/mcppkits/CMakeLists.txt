project(mcppkits VERSION 0.0.1)

set(MCPPKITS_INCLUDE_HOME "${SOLUTION_INCLUDE_HOME}/mcppkits")
set(MCPPKITS_SRC_HOME "${SOLUTION_SRC_HOME}/mcppkits")

message(STATUS "[mcppkits] CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "[mcppkits] BUILD_SHARED: ${BUILD_SHARED}")
message(STATUS "[mcppkits] BUILD_STATIC: ${BUILD_STATIC}")
message(STATUS "[mcppkits] MCPPKITS_INCLUDE_HOME: ${MCPPKITS_INCLUDE_HOME}")
message(STATUS "[mcppkits] MCPPKITS_SRC_HOME: ${MCPPKITS_SRC_HOME}")

set(mcppkits_headers
  ${MCPPKITS_INCLUDE_HOME}/mcppkits.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_config_file_reader.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_count_down_latch.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_dbgutils.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_fileutils.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_fixed_size_string.hpp
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_fps.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_md5.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_raii_wrapper.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_random.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_singleton.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_singletonp.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_strutils.h
  ${MCPPKITS_INCLUDE_HOME}/mcppkits_uuid.h
)

set(mcppkits_srcs
  ${MCPPKITS_SRC_HOME}/mcppkits.cpp
  ${MCPPKITS_SRC_HOME}/mcppkits_config_file_reader.cpp
  ${MCPPKITS_SRC_HOME}/mcppkits_count_down_latch.cpp
  ${MCPPKITS_SRC_HOME}/mcppkits_fileutils.cpp
  ${MCPPKITS_SRC_HOME}/mcppkits_md5.cpp
  ${MCPPKITS_SRC_HOME}/mcppkits_random.cpp
  ${MCPPKITS_SRC_HOME}/mcppkits_strutils.cpp
  ${MCPPKITS_SRC_HOME}/mcppkits_uuid.cpp
)

if(BUILD_SHARED)
  add_library(mcppkits SHARED ${mcppkits_srcs})
  target_include_directories(mcppkits PUBLIC
    ${SOLUTION_INCLUDE_HOME}
  )
  target_link_libraries(mcppkits ${mcppkits_libs})
  target_compile_options(mcppkits PRIVATE ${mcppkits_compile_options})
  target_link_options(mcppkits PRIVATE ${mcppkits_link_options})
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
    ${SOLUTION_INCLUDE_HOME}
  )
  target_link_libraries(mcppkits_static ${mcppkits_libs})
  target_compile_options(mcppkits_static PRIVATE ${mcppkits_compile_options})
  target_link_options(mcppkits_static PRIVATE ${mcppkits_link_options})
  install(TARGETS mcppkits_static
    ARCHIVE DESTINATION lib
  )
  add_custom_target(libmcppkits_static DEPENDS mcppkits_static)
endif()

install(DIRECTORY ${MCPPKITS_INCLUDE_HOME} DESTINATION include)
