#include "TcpServer.h"
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
TcpServer::TcpServer(std::string const &ip, int port, int reuseAddress,
                     int connections, bool shouldBlock)
    : shouldBlock_(shouldBlock) {
  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
    perror("Failed to set SIGPIPE to ignore");
  }
  ipAddr_ = Ipv4Address(ip, port);
  socketFd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socketFd_ < 0) {
    perror("Error creating server socket");
  }

  if (setsockopt(socketFd_, SOL_SOCKET, SO_REUSEADDR, &reuseAddress,
                 sizeof(reuseAddress)) < 0) {
    perror("setsockopt(SO_REUSEADDR) failed");
  }
  if (!shouldBlock_) {
    fcntl(socketFd_, F_SETFL, O_NONBLOCK);
  }

  if (bind(socketFd_, (const IpAddress *)&ipAddr_, sizeof(ipAddr_)) < 0) {
    perror("Error binding");
  }

  if (listen(socketFd_, connections) < 0) {
    perror("Error on listen");
  }
}
std::unique_ptr<TcpSocket> TcpServer::getClient() {
  // clilen = sizeof(cli_addr);
  // newsockfd = accept(sockfd,
  //   (struct sockaddr *) &cli_addr,
  //   &clilen);
  SocketDescriptor clientFd = -1;
  IpAddress clientAddr;
  socklen_t clientAddrSize = sizeof(clientAddr);
  clientFd = accept(socketFd_, &clientAddr, &clientAddrSize);

  if (clientFd < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return NULL;
    }
    perror("Error on accept");
  }
  return std::unique_ptr<TcpSocket>(new TcpSocket(clientFd));
}
TcpServer::~TcpServer() { close(socketFd_); }