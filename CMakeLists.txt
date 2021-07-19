cmake_minimum_required(VERSION 3.20)
get_filename_component(dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${dir_name})
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_GENERATOR "Ninja")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_compile_definitions(QT_DECLARATIVE_DEBUG QT_QML_DEBUG)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(deps/cmake-qmlplugin/QmlPlugin.cmake)
add_subdirectory(src)