cmake_minimum_required(VERSION 3.0)
project(plugin_manager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c89 -Wall -Wextra")

set(SOURCE_FILES main.cpp plugin_load.cpp)
add_executable(plugin_manager ${SOURCE_FILES})
target_link_libraries(plugin_manager ${CMAKE_DL_LIBS})

set(CMAKE_BUILD_TYPE Release)

set(SOURCE_FILES_ECHO plugin_echo.c)
add_library(plugin_echo SHARED ${SOURCE_FILES_ECHO})

set(SOURCE_FILES_DATETIME plugin_datetime.cpp)
add_library(plugin_datetime SHARED ${SOURCE_FILES_DATETIME})
