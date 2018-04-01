cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
include_directories(include)
add_library(sockets src/TcpSocket.cpp src/TcpServer.cpp src/Ipv4Address.cpp)
