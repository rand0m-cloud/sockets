#pragma once
#include "sockets/Sockets.h"
#include <mutex>
#include <thread>
#include <vector>
class PrintServer : public TcpServer {
private:
  // std::vector<std::thread> threads_;
  std::thread serveThread_;
  // int numThreads_;
  std::mutex socketLock_;
  std::ostream &output_;
  std::mutex &outputMutex_;
  bool shouldRun_ = true;
  void serve();
  void handleClient(TcpSocket *client, int num);
  void stop();

public:
  PrintServer(std::string const &ip, int port, bool reuseAddress,
              std::ostream &output, std::mutex &ostream_mutex);
  ~PrintServer();
  void waitForStop();
  PrintServer(const PrintServer &) = delete;
  PrintServer &operator=(const PrintServer &) = delete;
};