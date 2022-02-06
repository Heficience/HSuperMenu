cmake_minimum_required(VERSION 3.5)

if(WIN32)
    project(hsupermenu VERSION "4.20")
else()
    project(hsupermenu LANGUAGES CXX VERSION "4.20")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
    set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\msvc2019_64")
elseif(UNIX AND NOT APPLE)
    set(CMAKE_PREFIX_PATH "/home/paul/Qt/5.15.2/gcc_64/lib/cmake")
else()
    set(CMAKE_PREFIX_PATH "/Users/paulw/Qt/5.15.2/clang_64")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9")
endif()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if(APPLE)
set(CMAKE_MACOSX_BUNDLE ON)
endif()

if (UNIX)
    set(CMAKE_CXX_STANDARD 14)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O2")
endif()

find_package(QT NAMES Qt5 COMPONENTS Core REQUIRED)
find_package(QT NAMES Qt5 COMPONENTS Gui REQUIRED)
find_package(QT NAMES Qt5 COMPONENTS Svg REQUIRED)
find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Svg REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/resource.qrc
        src/icon.rc)

if (WIN32)
    qt5_add_resources(src/icon.rc)
endif()

if(WIN32)
    SET(GUI_TYPE WIN32)
else()
    SET(GUI_TYPE )
endif()



if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hsupermenu
            ${PROJECT_SOURCES}
            )
else()
    if(ANDROID)
        add_library(hsupermenu SHARED
                ${PROJECT_SOURCES}
                )
    else()
        add_executable(hsupermenu
                ${GUI_TYPE}
                ${PROJECT_SOURCES}
                )
    endif()
endif()

target_link_libraries(hsupermenu
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Svg
        Qt${QT_VERSION_MAJOR}::Widgets)

if (UNIX AND NOT APPLE)
    install(TARGETS hsupermenu
            RUNTIME DESTINATION bin)
    install(FILES src/hsupermenu.desktop DESTINATION share/applications)
    install(FILES Images/Heficience_Icone.svg DESTINATION share/icons/hicolor/scalable/apps/)
endif()
 
