add_library(tw_delivery_data INTERFACE)

target_include_directories(tw_delivery_data INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(tw_delivery_data INTERFACE tw::delivery::core)

add_library(tw::delivery::data ALIAS tw_delivery_data)
