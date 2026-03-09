include(FetchContent)
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(json)

add_executable(tw_delivery main.cpp)
target_link_libraries(tw_delivery PRIVATE
    nlohmann_json::nlohmann_json
    tw::delivery::dto
    tw::delivery::service
)

