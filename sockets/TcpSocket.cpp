#include "TcpSocket.h"
#include "Types.h"
#include <arpa/inet.h>
#include <cstring>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

TcpSocket::TcpSocket(std::string const &ip, int port) {
  ipAddr_ = Ipv4Address(ip, port);
  socketFd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socketFd_ < 0) {
    perror("Creating socket failed");
  }
  if (connect(socketFd_, (IpAddress *)&ipAddr_, sizeof(ipAddr_)) < 0) {
    perror("Error connecting socket");
  }
}
TcpSocket::TcpSocket(SocketDescriptor fd) {
  if (fd < 0) {
    std::cout << "TcpSocket was supplied with invalid fd";
  }
  socketFd_ = fd;
}

bool TcpSocket::sendString(const std::string &string) {

  if (send(socketFd_, &string[0], string.size(), 0) < 0) {
    perror("Failed to write to client");
    return false;
  }
  return true;
}

bool TcpSocket::getString(std::string &string) {
  if (recv(socketFd_, &string[0], string.size(), 0) < 0) {
    perror("Failed to recieve");
    return false;
  }

  return true;
}
TcpSocket::~TcpSocket() {
  if (socketFd_ > 0) {
    if (close(socketFd_) < 0) {
      perror("Failed to close socket");
    }
  }
}
