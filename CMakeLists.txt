cmake_minimum_required(VERSION 3.26)

project(UdpSort
  VERSION 0.1.0
  LANGUAGES CXX)

# Setting up default compile flags for Clang compiler id
include(cmake/add_clang_compile_options.cmake)

# Enforce debug as default build type
include(cmake/enforce_default_debug_build_type.cmake)

# TODO: industrialize coverage

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

subdirs("src" "tests")
