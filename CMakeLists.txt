cmake_minimum_required(VERSION 3.2)
project(ohMyGameBoy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ohMyGameBoy/CPU.cpp
    ohMyGameBoy/CPU.h
    ohMyGameBoy/MemoryUnit.cpp
    ohMyGameBoy/MemoryUnit.h
    ohMyGameBoy/main.cpp)

add_executable(ohMyGameBoy ${SOURCE_FILES})