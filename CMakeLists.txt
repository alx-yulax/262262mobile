cmake_minimum_required(VERSION 3.20)
project(262mobile)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

add_executable(262mobile main.cpp)
