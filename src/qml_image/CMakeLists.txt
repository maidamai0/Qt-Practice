cmake_minimum_required(VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${TARGET} CXX)
set(Qt6_COMPONENTS
    Core
    Quick
    QuickWidgets
    Qml
)

find_package(Qt6 COMPONENTS ${Qt6_COMPONENTS} REQUIRED)

foreach(LIB ${Qt6_COMPONENTS})
    link_libraries(Qt6::${LIB})
endforeach()

file(GLOB src "*.cpp")

add_executable(${TARGET} ${src} resource.qrc)

add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_CURRENT_SOURCE_DIR}/../ $<TARGET_FILE:${TARGET}>
)

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/../update_resource.py ${CMAKE_CURRENT_SOURCE_DIR})