cmake_minimum_required(VERSION 2.8)
project(BUScheduler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Process.h Process.cpp )
add_executable(BUScheduler ${SOURCE_FILES})