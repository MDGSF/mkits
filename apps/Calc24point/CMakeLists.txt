set(PROJECT_HOME ${SOLUTION_HOME}/apps/Calc24point)

add_executable(Calc24Server
  ${PROJECT_HOME}/Calc24Server/main.cpp
  ${PROJECT_HOME}/Calc24Server/TCPServer.cpp
  ${PROJECT_HOME}/Calc24Server/Player.cpp
  ${PROJECT_HOME}/net/ByteBuffer.cpp
  ${PROJECT_HOME}/net/Epoll.cpp
  ${PROJECT_HOME}/net/EventLoop.cpp
  ${PROJECT_HOME}/net/Poll.cpp
  ${PROJECT_HOME}/net/Select.cpp
  ${PROJECT_HOME}/net/TCPConnection.cpp
  ${PROJECT_HOME}/net/TCPServer.cpp
  ${PROJECT_HOME}/net/ThreadPool.cpp
)
target_include_directories(Calc24Server PUBLIC
  ${PROJECT_HOME}
)
target_link_libraries(Calc24Server PRIVATE mckits mcppkits m dl rt)
target_compile_options(Calc24Server PRIVATE -pthread)
target_link_options(Calc24Server PRIVATE -pthread)

add_executable(Calc24Client
  ${PROJECT_HOME}/Calc24Client/main.cpp
  ${PROJECT_HOME}/Calc24Client/TCPClient.cpp
)
target_link_libraries(Calc24Client PRIVATE mckits mcppkits m dl rt)
target_compile_options(Calc24Client PRIVATE -pthread)
target_link_options(Calc24Client PRIVATE -pthread)
