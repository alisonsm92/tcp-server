cmake_minimum_required(VERSION 3.10)
project(c-challenge)
add_executable(server main.cpp)
find_package(Boost REQUIRED COMPONENTS filesystem)