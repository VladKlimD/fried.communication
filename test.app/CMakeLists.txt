cmake_minimum_required(VERSION 3.5.0)

add_executable(test.app main.cpp)

target_link_libraries(test.app PRIVATE fried.communication)