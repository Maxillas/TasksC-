cmake_minimum_required(VERSION 3.5)

project(FindPathTask VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(HEADERS
    UI/blocks/field/field_view.h
    UI/blocks/field/cell.h

    UI/blocks/field_wrapper.h
    UI/blocks/size_setting.h
    UI/left_side.h
    UI/right_side.h
    UI/main_window.h

    Core/pathfinder.h
    Core/field_controller.h
)

set(SOURCES
    main.cpp
    UI/blocks/field/field_view.cpp
    UI/blocks/field_wrapper.cpp
    UI/blocks/size_setting.cpp
    UI/left_side.cpp
    UI/right_side.cpp
    UI/main_window.cpp

    Core/pathfinder.cpp
    Core/field_controller.cpp

)

add_executable(FindPathTask ${SOURCES}
)

target_link_libraries(FindPathTask PRIVATE Qt6::Widgets)

