#include <iostream>
#ifdef CMAKE
#include "Sockets.h"
#else
#warning Not using Cmake
#include "sockets/Sockets.h"
#endif

int main(int argc, char **argv) {
  std::cout << "server" << std::endl;
  if (argc != 3) {
    std::cout << argv[0] << " host port" << std::endl;
    return -1;
  }
  TcpSocket *test = new TcpSocket(argv[1], std::stoi(argv[2]));
  std::string data(4, 0);
  test->sendString("GET\r\n");
  test->getString(data);

  std::cout << data << std::endl;
}