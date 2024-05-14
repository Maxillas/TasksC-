cmake_minimum_required(VERSION 3.5)

project(CScpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CScpp main.cpp task1_2_4.cpp task1_2_10.cpp)

install(TARGETS CScpp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

set(SOURCES
    task1_2_4.cpp
    task1_2_10.cpp
    main.cpp

)
