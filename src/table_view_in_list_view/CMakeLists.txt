get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(Qt${QT_VERSION_MAJOR}_COMPONENTS
    Core
    Widgets
    Quick
    QuickWidgets
    Qml
)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${Qt${QT_VERSION_MAJOR}_COMPONENTS} REQUIRED)

foreach(LIB ${Qt${QT_VERSION_MAJOR}_COMPONENTS})
    link_libraries(Qt${QT_VERSION_MAJOR}::${LIB})
endforeach()

file(GLOB src "*.cpp")

add_executable(${TARGET} ${src} resource.qrc)

add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${deployqt} ${DEPLOY_PDB} --qmldir ${CMAKE_CURRENT_SOURCE_DIR}/../ $<TARGET_FILE:${TARGET}>
)

execute_process(COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/../update_resource.py ${CMAKE_CURRENT_SOURCE_DIR})