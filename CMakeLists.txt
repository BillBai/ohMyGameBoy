cmake_minimum_required(VERSION 3.2)
project(ohMyGameBoy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    ohMyGameBoy/GBCPU.cpp
    ohMyGameBoy/GBCPU.h
    ohMyGameBoy/GBMemoryUnit.cpp
    ohMyGameBoy/GBMemoryUnit.h
    ohMyGameBoy/main.cpp)

add_executable(ohMyGameBoy ${SOURCE_FILES})