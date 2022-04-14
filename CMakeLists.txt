cmake_minimum_required(VERSION 3.21)
project(Lab2)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(Lab2 src/main.cpp src/fileTools.cpp include/fileTools.h include/user_info.h src/user_info.cpp)
