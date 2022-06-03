cmake_minimum_required(VERSION 3.18.0)
#CMP0099 set to New by cmake_minimum_required

project(test_sycl CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR})
find_package(IntelDPCPP CONFIG REQUIRED)

add_library(OpenMP::OpenMP INTERFACE IMPORTED)
if(ENABLE_OPENMP)
  find_package(OpenMP)
  target_compile_options(OpenMP::OpenMP INTERFACE ${OpenMP_CXX_FLAGS})
endif()

add_library(myfoo sycl_device_code.cpp)
target_link_libraries(myfoo PUBLIC OneAPI::DPCPP-device)

add_library(myboo sycl_host_calls.cpp)
target_link_libraries(myboo PUBLIC OneAPI::DPCPP-host OpenMP::OpenMP)

add_executable(test_app main.cpp)
target_link_libraries(test_app PUBLIC myboo myfoo)
