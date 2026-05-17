cmake_minimum_required(VERSION 3.22)

project(resource_viewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(resource_viewer
    src/main.cpp
    src/MemScanner.cpp
    src/ScanResVisitor.cpp
    src/ScannerManager.cpp
    src/CPUScanner.cpp
)

target_include_directories(resource_viewer PRIVATE include thirdparty/nlohmann_json thirdparty/webui/include)

#link_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/webui)
target_link_libraries(resource_viewer PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/webui/libwebui-2.so"
    pthread m dl
)
