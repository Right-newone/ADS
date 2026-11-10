cmake_minimum_required(VERSION 4.2)

set(CMAKE_CXX_MODULE_STD ON)

add_executable("practice1")

target_compile_features("practice1" PUBLIC cxx_std_23)

target_sources("practice1"
  PRIVATE
    "main.cpp")