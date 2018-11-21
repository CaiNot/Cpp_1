cmake_minimum_required(VERSION 3.12)
project(Cpp_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS -static)

add_executable(Cpp_1 main.cpp)