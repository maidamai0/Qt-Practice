get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)



set(Qt${QT_VERSION_MAJOR}_COMPONENTS
    Core
)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS ${Qt${QT_VERSION_MAJOR}_COMPONENTS} REQUIRED)

foreach(LIB ${Qt${QT_VERSION_MAJOR}_COMPONENTS})
    link_libraries(Qt${QT_VERSION_MAJOR}::${LIB})
endforeach()

file(GLOB src "*.cpp")

add_executable(${TARGET} ${src})

if(${deployqt})
    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        COMMAND ${deployqt} ${DEPLOY_PDB} $<TARGET_FILE:${TARGET}>
    )
endif()