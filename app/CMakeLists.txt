add_executable(tw_delivery main.cpp)

target_link_libraries(tw_delivery PRIVATE
    tw::delivery::dto
    tw::delivery::data
    tw::delivery::service
    tw::delivery::infra
)

