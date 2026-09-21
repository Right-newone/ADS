cmake_minimum_required(VERSION 4.2)

set(CMAKE_CXX_MODULE_STD ON)

add_executable("ADS-laba1")

target_compile_features("ADS-laba1" PUBLIC cxx_std_23)

target_sources("ADS-laba1"
  PRIVATE
    "main.cpp"
  PRIVATE FILE_SET "modules" TYPE CXX_MODULES FILES
 "classes.cppm" "functions.cppm" "menu.cppm")