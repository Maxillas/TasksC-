cmake_minimum_required(VERSION 3.16)

project(MediaPlayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)

qt_standard_project_setup()

qt_add_executable(appMediaPlayer
    main.cpp
)

qt_add_qml_module(appMediaPlayer
    URI MediaPlayer
    VERSION 1.0
    QML_FILES
        UI/Main.qml
        UI/Blocks/Bottom.qml
        UI/Blocks/UpperLeft.qml
        UI/Blocks/UpperRight.qml
        UI/Components/ButtonStandart.qml
        QML_FILES UI/Blocks/ParametersView.qml
        QML_FILES UI/Components/ProgressBar.qml
        QML_FILES UI/Components/ButtonRound.qml
        QML_FILES UI/Resources/forward.png
        QML_FILES UI/Resources/backward.png
        QML_FILES UI/Resources/pause.png
        QML_FILES UI/Resources/play.png
        QML_FILES UI/Resources/repeat.png
        QML_FILES UI/Resources/stop.png
    SOURCES
        Core/mediaplayer.h Core/mediaplayer.h
        Core/mediaplayer.h Core/mediaplayer.cpp
        SOURCES Core/playlistmodel.h Core/playlistmodel.cpp
        SOURCES Core/playlistmanager.h Core/playlistmanager.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
# set_target_properties(appMediaPlayer PROPERTIES
# #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appMediaPlayer
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

target_link_libraries(appMediaPlayer
    PUBLIC Qt6::Multimedia

    PRIVATE Qt6::Quick

)

include(GNUInstallDirs)
install(TARGETS appMediaPlayer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
