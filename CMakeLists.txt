cmake_minimum_required(VERSION 3.1.0)
project(gps)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set(CMAKE_CXX_STANDARD 11)
add_compile_definitions(GPS_LOADABLE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Positioning REQUIRED)

add_library(gps SHARED
        GPS_global.h
        GPS.cpp
        GPS.h

        Logger/Logger.h
        Logger/Logger.cpp
        )

target_link_libraries(gps PUBLIC Qt5::Widgets Qt5::Positioning)
target_compile_definitions(gps PUBLIC GPS_LIBRARY)

install(TARGETS gps
        LIBRARY DESTINATION lib/carpi)
