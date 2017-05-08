cmake_minimum_required(VERSION 3.6)
project(UdpTask)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Drawer.cpp Drawer.h Communicator.cpp Communicator.h Perifery.cpp Perifery.h HardwareEndpoints.h)
add_executable(UdpTask ${SOURCE_FILES})