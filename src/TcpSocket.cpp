#include "TcpSocket.h"
#include "Types.h"
// #include <arpa/inet.h>
// #include <cstring>
// #include <errno.h>
// #include <iostream>
// #include <netinet/in.h>
// #include <sys/ioctl.h>
// #include <sys/socket.h>
#include <cstring>
#include <signal.h>
#include <unistd.h>
#include <vector>

TcpSocket::TcpSocket(std::string const &ip, int port) {

  ipAddr_ = Ipv4Address(ip, port);
  socketFd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socketFd_ < 0) {
    perror("Creating socket failed");
    return;
  }
  if (connect(socketFd_, (IpAddress *)&ipAddr_, sizeof(ipAddr_)) < 0) {
    perror("Error connecting socket");
    socketFd_ = -1;
  }
}
TcpSocket::TcpSocket(SocketDescriptor fd) {
  if (fd < 0) {
    std::cout << "TcpSocket was supplied with invalid fd";
  }
  socketFd_ = fd;
}

bool TcpSocket::sendData(const std::string &message) {
  if (socketFd_ < 0) {
    std::cout << "Socket is invalid" << std::endl;
    return false;
  }
  if (send(socketFd_, message.data(), message.size(), 0) < 0) {
    perror("Failed to write to client");
    return false;
  }
  return true;
}

int TcpSocket::getData(std::vector<char> &message) {
  if (socketFd_ < 0) {
  }
  std::vector<char> buffer(4096, 0);
  int dataRecieved = 0;
  int totalData = 0;
  do {
    dataRecieved = recv(socketFd_, &buffer[0], buffer.size(), 0);
    if (dataRecieved < 0) {
      perror("Failed to recieve");
      return -1;
    }
    message.reserve(totalData + dataRecieved);
    message.insert(message.end(), buffer.begin(),
                   buffer.begin() + dataRecieved);
    totalData += dataRecieved;
  } while (dataRecieved == buffer.size());

  return totalData;
}
TcpSocket::~TcpSocket() {
  std::cout << "socket deconstruction" << std::endl;
  if (socketFd_ > 0) {
    if (close(socketFd_) < 0) {
      perror("Failed to close socket");
    }
  }
}
