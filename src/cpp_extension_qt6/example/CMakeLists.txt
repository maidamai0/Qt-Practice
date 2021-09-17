project(cpp_extension_qt6 CXX)

file(GLOB src "*.cpp")
file(GLOB qrc "*.qrc")

add_executable(${PROJECT_NAME} ${src} ${qrc})
target_link_libraries(${PROJECT_NAME} module)