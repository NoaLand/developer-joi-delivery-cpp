add_executable(tw_delivery main.cpp)

target_link_libraries(tw_delivery PRIVATE
    tw::delivery::service
    tw::delivery::infra
)

