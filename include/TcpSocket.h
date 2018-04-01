#pragma once
#include "Types.h"
#include <vector>
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
  bool sendData(const std::string &message);
  int getData(std::vector<char> &message);
};
