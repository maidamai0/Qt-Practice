cmake_minimum_required(VERSION 3.10)
get_filename_component(TARGET ${CMAKE_CURRENT_SOURCE_DIR} NAME)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui REQUIRED)

file(GLOB src "*.cpp")
file(GLOB hdr "*.h")

add_executable(${TARGET} ${src} ${hdr})

target_link_libraries(${TARGET} Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)

add_custom_command(
    TARGET ${TARGET}
    POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_CURRENT_SOURCE_DIR}/../ $<TARGET_FILE:${TARGET}>
)
