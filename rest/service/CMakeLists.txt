add_library(tw_delivery_service INTERFACE)

target_include_directories(tw_delivery_service INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(tw_delivery_service INTERFACE
    tw::delivery::domain
    tw::delivery::dto
    tw::delivery::data
)

add_library(tw::delivery::service ALIAS tw_delivery_service)
