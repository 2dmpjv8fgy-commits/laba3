cmake_minimum_required(VERSION 3.10)
project(formatter_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотеки
add_library(formatter STATIC formatter_lib/formatter.cpp)
add_library(formatter_ex STATIC formatter_ex_lib/formatter_ex.cpp)
add_library(solver STATIC solver_lib/solver.cpp)

# Указываем пути к заголовкам для всех
include_directories(formatter_lib formatter_ex_lib solver_lib)

# Сборка Hello World
add_executable(hello_world hello_world_application/main.cpp)
target_link_libraries(hello_world formatter)

# Сборка Solver App
add_executable(solver_app solver_application/main.cpp)
target_link_libraries(solver_app formatter solver)
