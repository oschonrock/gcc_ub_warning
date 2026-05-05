cmake_minimum_required(VERSION 3.16)
project(ub)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 12.1.0
)
FetchContent_MakeAvailable(fmt)

add_executable(ub ub.cpp)
target_compile_features(ub PRIVATE cxx_std_26)
target_link_libraries(ub PRIVATE fmt)
