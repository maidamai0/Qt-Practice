cmake_minimum_required(VERSION 3.10)
get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

file(GLOB src "*.cpp")
file(GLOB hdr "*.h")

add_executable(${TARGET} ${src} ${hdr})

target_link_libraries(${TARGET} Qt6::Core Qt6::Gui Qt6::Widgets)

add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_CURRENT_SOURCE_DIR}/../ $<TARGET_FILE:${TARGET}>
)
