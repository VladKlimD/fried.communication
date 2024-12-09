cmake_minimum_required(VERSION 3.5.0)
project(fried.communication LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(fried.communication STATIC
    headers/fried_communication.h
    src/fried_communication.cpp
)

target_include_directories(fried.communication PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

add_subdirectory(test_app)