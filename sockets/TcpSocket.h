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
  bool sendString(std::string const &);
  bool getString(std::string &);
};
