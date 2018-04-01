#include "Types.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>

#include <netdb.h>

#include <sys/types.h>

Ipv4Address::Ipv4Address(std::string const &ip, int port) {
  std::memset(this, 0, sizeof(*this));

  if (!inet_pton(AF_INET, &ip[0], &(sin_addr))) {
    std::cout << "Trying string as hostname" << std::endl;
    struct addrinfo *result, hints;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM;
    int errorCode = getaddrinfo(&ip[0], NULL, &hints, &result);
    if (errorCode != 0) {
      gai_strerror(errorCode);
      return;
    }
    Ipv4Address *addr = (Ipv4Address *)result->ai_addr;
    std::memcpy(this, addr, sizeof(*this));
    freeaddrinfo(result);
  };
  sin_port = htons(port);
}
Ipv4Address::Ipv4Address() { std::memset(this, 0, sizeof(*this)); }
