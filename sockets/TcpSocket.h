#pragma once
#include "Types.h"
class TcpSocket {
private:
  Ipv4Address ipAddr_;

  SocketDescriptor socketFd_ = -1;

public:
  TcpSocket(std::string const &ip, int port);
  TcpSocket(SocketDescriptor fd);
  ~TcpSocket();
  TcpSocket(const TcpSocket &) = delete;
  TcpSocket &operator=(const TcpSocket &) = delete;
  bool sendData(const char *message, size_t size);
  int getData(char *message, size_t size);
};
