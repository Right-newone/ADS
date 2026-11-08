cmake_minimum_required(VERSION 4.2)

set(CMAKE_CXX_MODULE_STD ON)

add_executable("lab2")

target_compile_features("lab2" PUBLIC cxx_std_23)

target_sources("lab2"
  PRIVATE
    "main.cpp"
  PRIVATE FILE_SET "modules" TYPE CXX_MODULES FILES
    "classes.cppm" "menu.cppm")
