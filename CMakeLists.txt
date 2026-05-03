cmake_minimum_required(VERSION 3.10)
project(formatter_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(formatter_lib formatter_ex_lib solver_lib)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)

add_executable(hello_world hello_world_application/main.cpp)
target_link_libraries(hello_world formatter)

add_executable(solver_app solver_application/main.cpp)
target_link_libraries(solver_app formatter solver)
