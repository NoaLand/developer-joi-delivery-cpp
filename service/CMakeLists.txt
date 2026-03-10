add_library(tw_delivery_service STATIC
    src/CartService.cpp
    src/ProductService.cpp
    src/UserService.cpp
)

target_include_directories(tw_delivery_service PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(tw_delivery_service PRIVATE
    tw::delivery::core
    tw::delivery::dto
    tw::delivery::data
)

add_library(tw::delivery::service ALIAS tw_delivery_service)
