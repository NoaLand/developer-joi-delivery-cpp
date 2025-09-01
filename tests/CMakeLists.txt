enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${Boost_INCLUDE_DIRS})


add_executable(CartControllerTest controller/CartControllerTest.cpp)
target_link_libraries(CartControllerTest GTest::GTest GTest::Main pthread nlohmann_json::nlohmann_json)

add_test(NAME CartControllerTest COMMAND CartControllerTest)

