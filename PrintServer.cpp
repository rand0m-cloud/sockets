#include "PrintServer.h"
#include <mutex>
#include <thread>
#include <vector>
PrintServer::PrintServer(std::string const &ip, int port, bool reuseAddress,
                         std::ostream &output, std::mutex &outputMutex)
    : TcpServer(ip, port, reuseAddress, 5, true), output_(output),
      outputMutex_(outputMutex) {
  // threads_.reserve(numThreads_);
  // for (int i = 0; i < numThreads_; i++) {
  //   threads_.push_back(std::thread(&PrintServer::serve, this, i));
  // }
  serveThread_ = std::thread(&PrintServer::serve, this);
}

PrintServer::~PrintServer() {}
void PrintServer::serve() {
  int num = 0;
  while (shouldRun_) {
    socketLock_.lock();
    TcpSocket *client = TcpServer::getClient();
    socketLock_.unlock();
    if (client != NULL) {
      std::thread clientThread(&PrintServer::handleClient, this, client, num);
      clientThread.detach();
      num++;
    }
  }
}
void PrintServer::handleClient(TcpSocket *client, int num) {
  while (shouldRun_) {
    std::string response(4096, 0);
    if (client->getData(&response[0], response.size()) == 0) {
      break;
    }
    std::lock_guard<std::mutex> lock(outputMutex_);
    output_ << num << ":" << response << std::endl;
  }
  std::lock_guard<std::mutex> lock(outputMutex_);
  std::cout << num << ":"
            << "socket closed" << std::endl;
}
void PrintServer::waitForStop() { serveThread_.join(); }