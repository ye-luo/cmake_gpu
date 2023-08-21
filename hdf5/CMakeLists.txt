cmake_minimum_required(VERSION 3.21.0)
project(test_hdf5 C CXX)

#-------------------------------------------------------------------
#  set up HDF5 library
#-------------------------------------------------------------------
if(HAVE_MPI)
  option(HDF5_PREFER_PARALLEL "Request parallel/serial HDF5 library" ON)
else(HAVE_MPI)
  option(HDF5_PREFER_PARALLEL "Request parallel/serial HDF5 library" OFF)
  if(HDF5_PREFER_PARALLEL)
    message(FATAL_ERROR "Parallel HDF5 library cannot be selected with QMCPACK non-MPI build. "
                        "Please set HDF5_PREFER_PARALLEL=0.")
  endif(HDF5_PREFER_PARALLEL)
endif(HAVE_MPI)

if(QMC_BUILD_STATIC)
  message(STATUS "Linking static HDF5 library")
  set(HDF5_USE_STATIC_LIBRARIES on)
else()
  message(STATUS "Linking dynamic HDF5 library")
  set(HDF5_USE_STATIC_LIBRARIES off)
endif()

find_package(HDF5 1.10 COMPONENTS C)

if(HDF5_FOUND)
  if(HDF5_IS_PARALLEL)
    if(HAVE_MPI)
      message(STATUS "Parallel HDF5 library found")
      option(ENABLE_PHDF5 "Enable code paths using parallel HDF5" ON)
    else(HAVE_MPI)
      message(FATAL_ERROR "Parallel HDF5 library found but cannot be used with QMCPACK non-MPI build. "
                          "Please provide a serial HDF5 library or switch to building QMCPACK with MPI.")
    endif(HAVE_MPI)
  else(HDF5_IS_PARALLEL)
    message(STATUS "Serial HDF5 library found")
    option(ENABLE_PHDF5 "Enable code paths using parallel HDF5" OFF)
    if(ENABLE_PHDF5)
      if(HAVE_MPI)
        message(FATAL_ERROR "Parallel HDF5 code paths requested but serial HDF5 library found! "
                            "Please either provide parallel HDF5 library or set ENABLE_PHDF5=0.")
      else(HAVE_MPI)
        message(FATAL_ERROR "Parallel HDF5 code paths cannot be enabled on non-MPI builds! Please set ENABLE_PHDF5=0.")
      endif(HAVE_MPI)
    endif(ENABLE_PHDF5)
  endif(HDF5_IS_PARALLEL)

  if(ENABLE_PHDF5)
    message(STATUS "Using HDF5 parallel collective I/O code paths")
  else(ENABLE_PHDF5)
    message(STATUS "Using HDF5 non-scalable serial I/O code paths")
  endif(ENABLE_PHDF5)

  if(HAVE_MPI AND NOT ENABLE_PHDF5)
    message(
      WARNING
        "MPI builds may have performance loss by not using parallel HDF5! (Safe to ignore for workstation builds).")
  endif()

  if(CMAKE_BUILD_TYPE AND HDF5_LIBRARIES_DEBUG)
    if(CMAKE_BUILD_TYPE MATCHES DEBUG)
      set(HDF5_LIBRARIES ${HDF5_LIBRARIES_DEBUG})
    else()
      set(HDF5_LIBRARIES ${HDF5_LIBRARIES_RELEASE})
    endif()
  endif()

  add_library(IO::HDF5 INTERFACE IMPORTED)
  target_include_directories(IO::HDF5 INTERFACE "${HDF5_INCLUDE_DIR}")
  target_compile_definitions(IO::HDF5 INTERFACE "H5_USE_110_API")
  target_link_libraries(IO::HDF5 INTERFACE "${HDF5_LIBRARIES}")
  if(ENABLE_PHDF5)
    target_compile_definitions(IO::HDF5 INTERFACE "ENABLE_PHDF5")
  endif(ENABLE_PHDF5)
else(HDF5_FOUND)
  message(FATAL_ERROR "HDF5 not found. Set HDF5_ROOT")
endif(HDF5_FOUND)
