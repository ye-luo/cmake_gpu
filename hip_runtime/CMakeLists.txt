cmake_minimum_required(VERSION 3.21.0)

project(test_hip CXX)

add_executable(test_hip_runtime main.cpp)

if(HIPLANG)
  enable_language(HIP)
  set(CMAKE_HIP_LINKER_PREFERENCE_PROPAGATES 0)

  target_link_libraries(test_hip_runtime PUBLIC hip-lang::host)
else()
  find_package(HIP CONFIG)
  
  target_link_libraries(test_hip_runtime PUBLIC hip::host)
endif()
