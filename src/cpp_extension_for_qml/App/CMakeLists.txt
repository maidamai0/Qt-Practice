project(App CXX)

file(GLOB src "*.cpp")
file(GLOB qrc "*.qrc")

add_executable(${PROJECT_NAME} ${src} ${qrc})