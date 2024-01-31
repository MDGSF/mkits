file(GLOB TEST_SOURCES "test_*.cpp")
foreach(SOURCE ${TEST_SOURCES})
  get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
  add_executable(${EXECUTABLE_NAME} ${SOURCE})
  target_link_libraries(${EXECUTABLE_NAME} PRIVATE mcppkits m dl rt)
  target_compile_options(${EXECUTABLE_NAME} PRIVATE -pthread)
  target_link_options(${EXECUTABLE_NAME} PRIVATE -pthread)
endforeach()

file(GLOB UNITTEST_SOURCES "unittest_*.cpp")
foreach(SOURCE ${UNITTEST_SOURCES})
  get_filename_component(EXECUTABLE_NAME ${SOURCE} NAME_WE)
  add_executable(${EXECUTABLE_NAME} ${SOURCE})
  target_link_libraries(${EXECUTABLE_NAME} PRIVATE mcppkits m dl rt)
  target_compile_options(${EXECUTABLE_NAME} PRIVATE -pthread)
  target_link_options(${EXECUTABLE_NAME} PRIVATE -pthread)
  add_test(
    NAME ${EXECUTABLE_NAME}
    COMMAND $<TARGET_FILE:${EXECUTABLE_NAME}>
  )
endforeach()
