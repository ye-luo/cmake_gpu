cmake_minimum_required(VERSION 3.21.0)

project(test_hip CXX)
enable_language(HIP)
set(CMAKE_HIP_LINKER_PREFERENCE_PROPAGATES 0)
list(PREPEND CMAKE_PREFIX_PATH ${CMAKE_HIP_COMPILER_ROCM_ROOT})
find_package(hip CONFIG REQUIRED)
find_package(hipblas CONFIG REQUIRED)
find_package(rocsolver CONFIG REQUIRED)

get_target_property(HIPBLAS_INCLUDE roc::hipblas INTERFACE_INCLUDE_DIRECTORIES)
message("hipblas INTERFACE_INCLUDE_PATH = ${HIPBLAS_INCLUDE}")

add_Library(foo foo.hip.cpp)
set_source_files_properties(foo.hip.cpp PROPERTIES LANGUAGE HIP)

target_link_libraries(foo PUBLIC roc::hipblas roc::rocsolver)
add_executable(test_app main.cpp)
