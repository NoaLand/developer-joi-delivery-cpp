add_library(tw_delivery_core INTERFACE)

target_include_directories(tw_delivery_core INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(tw::delivery::core ALIAS tw_delivery_core)
