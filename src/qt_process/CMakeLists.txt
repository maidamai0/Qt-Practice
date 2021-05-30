cmake_minimum_required(VERSION 3.10)
project(qt_process CXX)

set(Qt6_COMPONENTS
    Core
)

find_package(Qt6 COMPONENTS ${Qt6_COMPONENTS} REQUIRED)

foreach(LIB ${Qt6_COMPONENTS})
    link_libraries(Qt6::${LIB})
endforeach()

add_executable(calling calling.cpp)
add_executable(called called.cpp)

add_custom_command(
    TARGET calling
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:calling>
)