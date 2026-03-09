cmake_minimum_required(VERSION 3.23)
project(developer_delivery_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(rest)
add_subdirectory(app)
add_subdirectory(tests)
