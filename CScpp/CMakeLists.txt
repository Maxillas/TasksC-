cmake_minimum_required(VERSION 3.5)

project(untitled2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(untitled2 main.cpp)

install(TARGETS untitled2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
