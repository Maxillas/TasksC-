cmake_minimum_required(VERSION 3.5)

project(Tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(HEADERS
        UI/edcwatcher.h
        Core/filemodelmanager.h
)

set(SOURCES
        main.cpp
        UI/edcwatcher.cpp
        Core/filemodelmanager.cpp
)

set(RESOURCES
        UI/Resources/system_tray_icon.svg)

add_executable(Tests ${SOURCES})

target_link_libraries(Tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(WIN32)
    message(STATUS "Configuring for Windows")

elseif(UNIX)
    message(STATUS "Configuring for Linux")

endif()
