cmake_minimum_required(VERSION 3.10)
project(model_view CXX)

set(Qt6_COMPONENTS
    Core 
    Gui
    Widgets
)

find_package(Qt6 COMPONENTS  ${Qt6_COMPONENTS} REQUIRED)

file(GLOB src "*.cpp")
file(GLOB hdr "*.h")

add_executable(${PROJECT_NAME} ${src} ${hdr})

foreach(LIB ${Qt6_COMPONENTS})
    target_link_libraries(${PROJECT_NAME} Qt6::${LIB})
endforeach()

