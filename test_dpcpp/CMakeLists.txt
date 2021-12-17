cmake_minimum_required(VERSION 3.18.0)

project(test_sycl CXX)
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(MyIntelDPCPP CONFIG REQUIRED)

add_library(myfoo foo.cpp)
target_link_libraries(myfoo PUBLIC OneAPI::DPCPP-device)

add_executable(test_app main.cpp)
target_link_libraries(test_app PUBLIC OneAPI::DPCPP-host myfoo)
