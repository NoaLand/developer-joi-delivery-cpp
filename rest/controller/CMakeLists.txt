add_library(controller INTERFACE)
# Turn off magic autolink esp for Windows
target_compile_definitions(Boost::headers INTERFACE BOOST_ALL_NO_LIB)
target_link_libraries(controller INTERFACE Boost::headers nlohmann_json::nlohmann_json domain service)
