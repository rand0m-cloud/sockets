#pragma once
#include "TcpSocket.h"
#include "Types.h"
#include <memory>
class TcpServer {
private:
  Ipv4Address ipAddr_;

  SocketDescriptor socketFd_ = -1;
  bool shouldBlock_;

public:
  TcpServer(std::string const &ip, int port, int reuseAddress, int connections,
            bool shouldBlock);
  ~TcpServer();
  TcpServer(const TcpServer &) = delete;
  TcpServer &operator=(const TcpServer &) = delete;
  std::unique_ptr<TcpSocket> getClient();
};
