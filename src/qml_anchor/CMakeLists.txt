cmake_minimum_required(VERSION 3.10)

get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${TARGET} CXX)
set(Qt${QT_VERSION_MAJOR}_COMPONENTS
    Core
    Quick
    QuickWidgets
    Qml
)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${Qt${QT_VERSION_MAJOR}_COMPONENTS} REQUIRED)

foreach(LIB ${Qt${QT_VERSION_MAJOR}_COMPONENTS})
    link_libraries(Qt${QT_VERSION_MAJOR}::${LIB})
endforeach()

file(GLOB src "*.cpp" "*.qml")

add_executable(${TARGET} ${src} resource.qrc)

if(${deployqt})
    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        COMMAND ${deployqt} ${DEPLOY_PDB} --qmldir ${CMAKE_CURRENT_SOURCE_DIR}/../ $<TARGET_FILE:${TARGET}>
    )
endif(${deployqt})

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/../update_resource.py ${CMAKE_CURRENT_SOURCE_DIR})