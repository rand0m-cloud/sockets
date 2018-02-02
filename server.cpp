#include "protobuffers/test.pb.h"
#include "sockets/Sockets.h"
#include <iostream>
// #warning Not using Cmake
// #include "sockets/Sockets.h"

int main(int argc, char **argv) {
  //  GOOGLE_PROTOBUF_VERIFY_VERSION;
  std::cout << "server" << std::endl;
  if (argc != 3) {
    std::cout << argv[0] << " host port" << std::endl;
    return -1;
  }
  HelloWorld message;
  message.set_message("Hello World!");
  message.set_test2("Test!");
  std::cout << message.message() << std::endl;
  std::cout << "size:" << message.ByteSize() << std::endl;
  TcpSocket *test = new TcpSocket(argv[1], std::stoi(argv[2]));
  std::string data(4, 0);
  test->sendString("GET\r\n");
  test->getString(data);
  std::cout << data << std::endl;
}