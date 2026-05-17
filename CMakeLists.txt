cmake_minimum_required(VERSION 3.22)

project(resource_viewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(resource_viewer
    src/main.cpp
    src/MemScanner.cpp
    src/ScanResVisitor.cpp
)

target_include_directories(resource_viewer PRIVATE include)
