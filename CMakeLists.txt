# Must use 'pip install "pybind11[global]"' to install pybind11 first. 

cmake_minimum_required(VERSION 3.31)

project(try_matrix LANGUAGES CUDA CXX)

include(CheckLanguage)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3 -Wall")
set(CMAKE_CUDA_FLAGS_RELEASE "-O3 -Wall")
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Python COMPONENTS Interpreter Development)
find_package(pybind11 CONFIG REQUIRED)

check_language(CUDA)
message("CMAKE_CUDA_COMPILER_ID : ${CMAKE_CUDA_COMPILER_ID}")
message("CMAKE_CUDA_COMPILER_VERSION : ${CMAKE_CUDA_COMPILER_VERSION}")

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} my_src_list)
message("SRC_FILES: ${my_src_list}")

pybind11_add_module(_matrix ${my_src_list})
