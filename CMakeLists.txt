cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE Debug)
project(TcpSockets)
#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIRS})

# I cant get sdl_net config to work
# find_package(SDL_net REQUIRED)
# include_directories(${SDL_NET_INCLUDE_DIRS})

add_definitions(-DCMAKE)

if(!UNIX)
  message(FATAL_ERROR "Sorry I have to use Unix sockets because I can't config SDL_Net")
endif()

include_directories("${PROJECT_SOURCE_DIR}/sockets")
add_subdirectory(sockets)

include_directories("${PROJECT_SOURCE_DIR}/protobuffers")
include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
add_subdirectory(protobuffers)


add_executable(Server server.cpp PrintServer.cpp)
target_link_libraries(Server sockets)
target_link_libraries(Server protobuffers)

add_executable(Client client.cpp)
target_link_libraries(Client sockets)
target_link_libraries(Client protobuffers)
#target_link_libraries(SDLNet ${SDL2_LIBRARIES})

#target_link_libraries(SDLNet ${SDL_NET_LIBRARIES})
