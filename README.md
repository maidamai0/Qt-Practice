# Practice code for [Qt](https://www.qt.io/)

These samples are originally written with Qt5 and now compile with Qt6

## How to build

[CMake](https://cmake.org/) and [Ninja](https://ninja-build.org/) are used to build these samples

* Latest CMake is recommended, but older version should work after you change `cmake_minimum_required` in [Top CMakeLists.txt](CMakeLists.txt)
* **Ninja** is used as the **CMake Generator**, you can use the default tool after comment out `set(CMAKE_GENERATOR "Ninja")` in [Top CMakeLists.txt](CMakeLists.txt)
* Make sure **CMake** can find Qt, such as `cmake -DCMAKE_PREFIX_PATH=C:/Qt/6.0.3/msvc2019_64/lib/cmake`