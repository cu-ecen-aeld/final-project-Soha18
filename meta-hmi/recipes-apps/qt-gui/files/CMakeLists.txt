cmake_minimum_required(VERSION 3.5)

project(guiapp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)  # <-- this handles your .ui files automatically
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Add your sources and UI files here
set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

set(UIS
    mainwindow.ui
)

# Build the executable with UI integration
add_executable(guiapp
    ${SOURCES}
    ${HEADERS}
    ${UIS}
)

target_link_libraries(guiapp Qt5::Widgets)

