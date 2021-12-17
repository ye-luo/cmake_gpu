cmake_minimum_required(VERSION 3.18.0)

project(test_sycl CXX)
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(IntelDPCPP CONFIG REQUIRED)

add_library(myfoo sycl_device_code.cpp)
target_link_libraries(myfoo PUBLIC OneAPI::DPCPP-device)

add_library(myboo sycl_device_code.cpp)
target_link_libraries(myboo PUBLIC OneAPI::DPCPP-host)

add_executable(test_app main.cpp)
target_link_libraries(test_app PUBLIC myboo myfoo)
