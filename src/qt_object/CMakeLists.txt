get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)



set(Qt6_COMPONENTS
    Core
)

find_package(Qt6 COMPONENTS ${Qt6_COMPONENTS} REQUIRED)

foreach(LIB ${Qt6_COMPONENTS})
    link_libraries(Qt6::${LIB})
endforeach()

file(GLOB src "*.cpp")

add_executable(${TARGET} ${src})

add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:${TARGET}>
)