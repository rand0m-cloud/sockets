#include "PrintServer.h"
#include "protobuffers/test.pb.h"
#include "sockets/Sockets.h"
#include <iostream>
#include <mutex>
// #warning Not using Cmake
// #include "sockets/Sockets.h"
// std::string message = "Hello\r\n";

// Protects std::cout from simultaneous writes
std::mutex cout_mutex;

proto::MessageContainer message;
proto::SimpleInt *intMessage = new proto::SimpleInt;
int main(int argc, char **argv) {
  GOOGLE_PROTOBUF_VERIFY_VERSION;
  std::cout << "server" << std::endl;
  if (argc != 3) {
    cout_mutex.lock();
    std::cout << argv[0] << " host port" << std::endl;
    cout_mutex.unlock();
    return -1;
  }
  PrintServer test(argv[1], std::stoi(argv[2]), true, std::cout, cout_mutex);
  // TcpSocket *client = test.getClient();
  //
  // intMessage->set_number(69);
  // message.set_allocated_simpleint(intMessage);
  // std::string data = message.SerializeAsString();
  // client->sendData(&data[0], data.size());
  // while (true) {
  //   std::string response(4096, 0);
  //   if (client->getData(&response[0], response.size()) == 0) {
  //     break;
  //   }
  //
  //   std::cout << response << std::endl;
  // }
  test.waitForStop();
  std::cout << "socket closed" << std::endl;
}