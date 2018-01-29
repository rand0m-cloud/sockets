#pragma once
#include "TcpSocket.h"
#include "Types.h"
class TcpServer {
private:
  Ipv4Address ipAddr_;

  SocketDescriptor socketFd_ = -1;

public:
  TcpServer(std::string const &ip, int port);
  ~TcpServer();
  TcpServer(const TcpServer &) = delete;
  TcpServer &operator=(const TcpServer &) = delete;
  TcpSocket *getClient();
};
