cmake_minimum_required(VERSION 3.10)
project(BallTree-v2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY $(CMAKE_BINARY_DIR)/../../../Interfaz_PythonFlask)

include_directories($(CMAKE_CURRENT_SOURCE_DIR)/src)

add_executable(BallTreeInterface src/BallTreeInterface.cpp)
add_executable(GenerateBallTree src/GenerateBallTree.cpp)