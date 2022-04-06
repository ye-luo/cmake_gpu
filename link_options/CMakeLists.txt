cmake_minimum_required(VERSION 3.17)
cmake_policy(SET CMP0099 NEW)

project(openmp-target LANGUAGES CXX)

add_library(qmc_openmp_cxx INTERFACE)
target_compile_options(qmc_openmp_cxx INTERFACE "${OPENMP_COMPILE_OPTIONS}")
target_link_options(qmc_openmp_cxx INTERFACE "${OPENMP_LINK_OPTIONS}")

add_library(abc abc.cpp)
target_link_libraries(abc PRIVATE qmc_openmp_cxx)

add_library(abc_noomp abc_noomp.cpp)
add_executable(test test.cpp)

target_link_libraries(test PRIVATE abc abc_noomp)
