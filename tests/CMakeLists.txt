include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.12.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(tw_delivery_test service/CartServiceTest.cpp)
target_link_libraries(tw_delivery_test PRIVATE
    gtest_main
    tw::delivery::dto
    tw::delivery::data
)

include(GoogleTest)
gtest_discover_tests(tw_delivery_test)
