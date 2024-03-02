set(PROJECT_HOME ${SOLUTION_HOME}/apps/math_study)

add_executable(math_study ${PROJECT_HOME}/main.cpp)
target_link_libraries(math_study PRIVATE mckits mcppkits m dl rt)
target_compile_options(math_study PRIVATE -pthread)
target_link_options(math_study PRIVATE -pthread)
