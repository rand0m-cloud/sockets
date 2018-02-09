#include "sockets/Sockets.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <thread>
int main(int argc, char **argv) {
  if (argc != 3) {

    std::cout << argv[0] << " host port" << std::endl;

    return -1;
  }

  std::random_device rd;
  std::uniform_int_distribution<int> uniformDistribution(100, 500);
  std::mt19937 generator(rd());

  int clientNum = uniformDistribution(generator);
  std::stringstream message;
  message << "Hello from client:" << clientNum << "\r\n";
  std::string finalMessage = message.str();

  TcpSocket test(argv[1], std::stoi(argv[2]));
  test.sendData(finalMessage.c_str(), finalMessage.size());

  std::stringstream periodicMessage;
  periodicMessage << "Client " << clientNum << " checking in"
                  << "\r\n";
  std::string finalPeriodicMessage = periodicMessage.str();

  while (test.sendData(finalPeriodicMessage.c_str(),
                       finalPeriodicMessage.size())) {
    std::this_thread::sleep_for(
        std::chrono::milliseconds(uniformDistribution(generator)));
  }
}