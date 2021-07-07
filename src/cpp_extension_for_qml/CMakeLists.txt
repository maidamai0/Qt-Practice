set(CMAKE_DEBUG_POSTFIX d)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Qml Quick REQUIRED)
link_libraries(Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Qml Qt${QT_VERSION_MAJOR}::Quick)
add_subdirectory(TimeModule)
add_subdirectory(App)