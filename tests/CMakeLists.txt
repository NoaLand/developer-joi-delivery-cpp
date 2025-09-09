enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${Boost_INCLUDE_DIRS})


add_executable(CartServiceTest service/CartServiceTest.cpp)
target_link_libraries(CartServiceTest GTest::GTest GTest::Main pthread nlohmann_json::nlohmann_json)

add_test(NAME CartServiceTest COMMAND CartServiceTest)
