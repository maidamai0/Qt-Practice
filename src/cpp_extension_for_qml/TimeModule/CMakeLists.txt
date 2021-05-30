

file(GLOB src "*.cpp")
file(GLOB hdr "*.h")

add_qmlplugin(TimeModule
    URI code.cpp_extension_for_qml.TimeModule
    VERSION 1.0
    SOURCES ${src} ${hdr} qmldir
)