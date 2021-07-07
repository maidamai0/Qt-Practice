cmake_minimum_required(VERSION 3.10)
project(qt_process CXX)

set(Qt${QT_VERSION_MAJOR}_COMPONENTS
    Core
)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${Qt${QT_VERSION_MAJOR}_COMPONENTS} REQUIRED)

foreach(LIB ${Qt${QT_VERSION_MAJOR}_COMPONENTS})
    link_libraries(Qt${QT_VERSION_MAJOR}::${LIB})
endforeach()

add_executable(calling calling.cpp)
add_executable(called called.cpp)

add_custom_command(
    TARGET calling
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} ${DEPLOY_PDB} $<TARGET_FILE:calling>
)