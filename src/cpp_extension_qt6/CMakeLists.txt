set(CMAKE_DEBUG_POSTFIX d)

find_package(Qt6 COMPONENTS Core Qml Quick REQUIRED)
link_libraries(Qt6::Core Qt6::Qml Qt6::Quick)
add_subdirectory(org/company/module)
add_subdirectory(example)