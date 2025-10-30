cmake_minimum_required(VERSION 3.19)
project(developer_joyofdelivery_cpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(Threads)

add_subdirectory(rest)
add_executable(app main.cpp)
target_link_libraries(app PRIVATE nlohmann_json::nlohmann_json)

enable_testing()
add_subdirectory(tests)
