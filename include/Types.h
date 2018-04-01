#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <netinet/ip.h>
typedef int SocketDescriptor;
typedef sockaddr IpAddress;
struct Ipv4Address : public sockaddr_in {
  Ipv4Address(std::string const &ip, int port);
  Ipv4Address();
};