cmake_minimum_required(VERSION 3.20)
project(MS3)

set(CMAKE_CXX_STANDARD 17)

add_executable(MS3 ms3.cpp Utilities.h Utilities.cpp Station.h Station.cpp CustomerOrder.h CustomerOrder.cpp Workstation.cpp Workstation.h LineManager.cpp LineManager.h)
