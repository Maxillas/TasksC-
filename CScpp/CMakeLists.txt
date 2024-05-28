cmake_minimum_required(VERSION 3.5)

project(CScpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CScpp main.cpp task1_2_4.cpp task1_2_10.cpp task1_4.cpp
    task2_1.cpp task2_2.cpp
    task2_3.cpp
    task3_2.cpp)

install(TARGETS CScpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(SOURCES
    task1_5.cpp
    task1_2_4.cpp
    task1_2_10.cpp
    task1_4.cpp
    task2_2.cpp
    main.cpp

)
