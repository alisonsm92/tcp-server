cmake_minimum_required(VERSION 3.10)
project(c-challenge)
add_executable(server main.cpp server.cpp session.cpp)
find_package(Boost REQUIRED COMPONENTS filesystem)