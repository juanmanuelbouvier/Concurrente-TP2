cmake_minimum_required(VERSION 3.6)
project(Cliente_BdD)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/Main.cpp include/ipc/Cola.h)
add_executable(Cliente_BdD ${SOURCE_FILES})