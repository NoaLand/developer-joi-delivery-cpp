add_library(tw_delivery_util INTERFACE)

target_include_directories(tw_delivery_util INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(tw_delivery_util INTERFACE
    tw::delivery::core
    tw::delivery::dto
)

add_library(tw::delivery::util ALIAS tw_delivery_util)
