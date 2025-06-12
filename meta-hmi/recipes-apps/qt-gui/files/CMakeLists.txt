cmake_minimum_required(VERSION 3.5)

project(guiapp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Source and header files
set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

# Build the executable
add_executable(guiapp
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(guiapp Qt5::Widgets)

