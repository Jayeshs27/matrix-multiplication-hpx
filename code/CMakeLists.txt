cmake_minimum_required(VERSION 3.16)
project(matmul_hpx CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(HPX REQUIRED)
add_executable(main main.cpp)
target_link_libraries(main HPX::wrap_main HPX::hpx HPX::iostreams_component)
