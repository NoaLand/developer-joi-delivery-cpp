add_library(tw_delivery_infra INTERFACE)

target_include_directories(tw_delivery_infra INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(tw_delivery_infra INTERFACE
    tw::delivery::core
    tw::delivery::dto
)

add_library(tw::delivery::infra ALIAS tw_delivery_infra)
