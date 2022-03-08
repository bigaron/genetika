cmake_minimum_required(VERSION 3.10)

project(genetika)

add_definitions(-DMEMTRACE)

add_executable(genetika genetika_teszt.cpp memtrace.cpp allapotgep.cpp)