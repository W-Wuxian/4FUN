cmake_minimum_required(VERSION 3.26)
project(
  4FUN
  VERSION 1.0.0
  LANGUAGES CXX C CUDA)
enable_language(CUDA)
include(CMakePrintHelpers)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# Set standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)

add_compile_definitions(WITH_CUDA USE_DOUBLE FIXSEED=1234567 WDEBUG)

# CUDA for NVHPC cuda_runtime.h
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
# set(CMAKE_CUDA_COMPILER ${CMAKE_CUDA_HOST_COMPILER})  # NVHPC nvc++/nvfortran
set(CMAKE_CUDA_ARCHITECTURES 86) # Adjust for your GPUs

# Find OpenBLAS (for cblas.h)
set(BLA_VENDOR OpenBLAS)
set(BLA_PREFER_PKGCONFIG ON)
find_package(BLAS REQUIRED)
# Find CUDA
find_package(CUDAToolkit REQUIRED)
# CUDA headers include_directories(${CUDAToolkit_INCLUDE_DIRS})

# Utils library (C utils: matgen, showmat, etc.)
set(UTIL_SOURCES
    "${PROJECT_SOURCE_DIR}/utils/src/handle_showmat.c"
    "${PROJECT_SOURCE_DIR}/utils/src/handle_matgen.c"
    "${PROJECT_SOURCE_DIR}/utils/src/handle_gpu_error.c"
    "${PROJECT_SOURCE_DIR}/utils/src/handle_compare_results.c"
    "${PROJECT_SOURCE_DIR}/utils/src/handle_type.c")
add_library(4fun_utils STATIC ${UTIL_SOURCES})
target_link_libraries(4fun_utils PRIVATE BLAS::BLAS)
set_target_properties(4fun_utils PROPERTIES LINKER_LANGUAGE C)

# GPU kernels library (NVHPC cuda_runtime.h only)
set(GPU_SOURCES
    "${PROJECT_SOURCE_DIR}/kernels/gpu/src/gpu_cblas_lvl1_d.cu"
    # "${PROJECT_SOURCE_DIR}/kernels/gpu/src/gpu_cblas_lvl2_d.cu"
    # "${PROJECT_SOURCE_DIR}/kernels/gpu/src/gpu_cblas_lvl3_d.cu"
)
add_library(4fun_gpu STATIC ${GPU_SOURCES})
target_link_libraries(4fun_gpu PRIVATE 4fun_utils CUDA::cudart)
set_target_properties(4fun_gpu PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

# Build type optimizations
target_compile_options(
  4fun_utils PRIVATE -Wall $<$<CONFIG:Release>:-O3 -march=native>
                     $<$<CONFIG:Debug>:-O0 -g>)

target_compile_options(
  4fun_gpu
  PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:
          -Xcompiler
          -Wall
          --ptxas-options=-v
          --use_fast_math
          $<$<CONFIG:Release>:-O3>
          $<$<CONFIG:Debug>:-G
          -g>
          >)
set_property(TARGET 4fun_gpu PROPERTY CUDA_ARCHITECTURES 86)

# SOURCE TREE INCLUDES utils
target_include_directories(
  4fun_utils SYSTEM
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
          ${CMAKE_CURRENT_SOURCE_DIR}/utils/include ${CUDAToolkit_INCLUDE_DIRS})
# SOURCE TREE INCLUDES gpu
target_include_directories(
  4fun_gpu SYSTEM
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
          ${CMAKE_CURRENT_SOURCE_DIR}/utils/include
          ${CMAKE_CURRENT_SOURCE_DIR}/kernels/gpu/include
          ${CUDAToolkit_INCLUDE_DIRS})

# Install
install(
  TARGETS 4fun_utils 4fun_gpu
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin)

# Install public main header FIRST
set(ALL_HEADERS
    "${PROJECT_SOURCE_DIR}/include/4fun.h"
    "${PROJECT_SOURCE_DIR}/include/common.h"
    "${PROJECT_SOURCE_DIR}/include/define_type.h"
    "${PROJECT_SOURCE_DIR}/utils/include/handle_showmat.h"
    "${PROJECT_SOURCE_DIR}/utils/include/handle_matgen.h"
    "${PROJECT_SOURCE_DIR}/utils/include/handle_gpu_error.h"
    "${PROJECT_SOURCE_DIR}/utils/include/handle_compare_results.h"
    "${PROJECT_SOURCE_DIR}/kernels/gpu/include/gpu_cblas_lvl1_d.h"
    "${PROJECT_SOURCE_DIR}/kernels/gpu/include/gpu_cblas_lvl2_d.h"
    "${PROJECT_SOURCE_DIR}/kernels/gpu/include/gpu_cblas_lvl3_d.h")
install(FILES ${ALL_HEADERS} DESTINATION include/4fun)

# EXEMPLES (GLOB récursif fixe)
file(GLOB_RECURSE EXAMPLE_SOURCES "example/**/*.cu")
foreach(EXAMPLE_FILE ${EXAMPLE_SOURCES})
  get_filename_component(EXAMPLE_NAME ${EXAMPLE_FILE} NAME_WE)
  cmake_print_variables(EXAMPLE_FILE EXAMPLE_NAME)

  add_executable(${EXAMPLE_NAME} ${EXAMPLE_FILE})
  target_link_libraries(${EXAMPLE_NAME} PRIVATE 4fun_utils 4fun_gpu BLAS::BLAS
                                                CUDA::cudart)

  target_include_directories(
    ${EXAMPLE_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
            ${CMAKE_CURRENT_SOURCE_DIR}/utils/include
            ${CMAKE_CURRENT_SOURCE_DIR}/kernels/cpu/include
            ${CMAKE_CURRENT_SOURCE_DIR}/kernels/gpu/include
            ${CUDAToolkit_INCLUDE_DIRS})

  set_target_properties(${EXAMPLE_NAME} PROPERTIES CUDA_STANDARD 17)

  install(TARGETS ${EXAMPLE_NAME} RUNTIME DESTINATION bin/examples)

endforeach()
