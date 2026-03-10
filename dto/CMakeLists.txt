add_library(tw_delivery_dto INTERFACE)

target_include_directories(tw_delivery_dto INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(tw_delivery_dto INTERFACE tw::delivery::core)

add_library(tw::delivery::dto ALIAS tw_delivery_dto)
