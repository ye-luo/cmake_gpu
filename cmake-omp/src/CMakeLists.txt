cmake_minimum_required(VERSION 3.22)
project(debug-cce Fortran C)

add_library(qe_openmp_fortran INTERFACE)
add_library(qe_openmp_c INTERFACE)

find_package(OpenMP REQUIRED Fortran C)
target_link_libraries(qe_openmp_fortran INTERFACE OpenMP::OpenMP_Fortran)
target_link_libraries(qe_openmp_c INTERFACE OpenMP::OpenMP_C)

foreach(LANG Fortran C)
  message("OpenMP_${LANG}_FLAGS ${OpenMP_${LANG}_FLAGS}")
  message("OpenMP_${LANG}_LIBRARIES ${OpenMP_${LANG}_LIBRARIES}")
endforeach()

# Fortran
add_library(boo_f boo.f90)
target_link_libraries(boo_f PRIVATE qe_openmp_fortran)
add_executable(boo_f_exe main.f90)
target_link_libraries(boo_f_exe PRIVATE boo_f)

# C
add_library(boo boo.c)
target_link_libraries(boo PRIVATE qe_openmp_c)
add_executable(boo_exe main.c)
target_link_libraries(boo_exe PRIVATE boo)
