cmake_minimum_required(VERSION 3.10)
project(model_view CXX)

set(Qt${QT_VERSION_MAJOR}_COMPONENTS
    Core 
    Gui
    Widgets
)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS  ${Qt${QT_VERSION_MAJOR}_COMPONENTS} REQUIRED)

file(GLOB src "*.cpp")
file(GLOB hdr "*.h")

add_executable(${PROJECT_NAME} ${src} ${hdr})

foreach(LIB ${Qt${QT_VERSION_MAJOR}_COMPONENTS})
    target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::${LIB})
endforeach()

