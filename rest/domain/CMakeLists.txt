add_library(tw_delivery_domain INTERFACE)

target_include_directories(tw_delivery_domain INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)

add_library(tw::delivery::domain ALIAS tw_delivery_domain)
