project(mcppkits VERSION 0.0.1)

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

if(BUILD_SHARED)
  add_library(mcppkits SHARED ${mcppkits_srcs})
  target_include_directories(mcppkits PUBLIC
    ${PROJECT_SOURCE_DIR}
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
    ${PROJECT_SOURCE_DIR}
  )
  target_link_libraries(mcppkits_static ${mcppkits_libs})
  target_compile_options(mcppkits_static PRIVATE ${mcppkits_compile_options})
  target_link_options(mcppkits_static PRIVATE ${mcppkits_link_options})
  install(TARGETS mcppkits_static
    ARCHIVE DESTINATION lib
  )
  add_custom_target(libmcppkits_static DEPENDS mcppkits_static)
endif()

install(FILES ${mcppkits_headers} DESTINATION include/mcppkits)
