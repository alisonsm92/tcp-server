cmake_minimum_required(VERSION 3.10)
project(c-challenge)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(server 
    server/main.cpp 
    server/server.cpp 
    server/session.cpp
)
target_link_libraries(server Boost::system)

add_executable(client 
    client/main.cpp
)
target_link_libraries(client Boost::system)
