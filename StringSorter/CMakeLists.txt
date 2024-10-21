cmake_minimum_required(VERSION 3.5)

project(sorter_test_task LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sorter_test_task main.cpp
    sortertests.h sortertests.cpp
    sorter.h sorter.cpp
)

include(GNUInstallDirs)
install(TARGETS sorter_test_task
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
