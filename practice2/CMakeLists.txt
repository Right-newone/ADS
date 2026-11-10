cmake_minimum_required(VERSION 4.2)

set(CMAKE_CXX_MODULE_STD ON)

add_executable("practice2")

target_compile_features("practice2" PUBLIC cxx_std_23)

target_sources("practice2"
  PRIVATE
    "main.cpp")