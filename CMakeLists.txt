cmake_minimum_required(VERSION 3.23)
project(developer_delivery_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(rest)

include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(json)

add_executable(tw_delivery main.cpp)
target_link_libraries(tw_delivery PRIVATE nlohmann_json::nlohmann_json)

add_subdirectory(tests)
