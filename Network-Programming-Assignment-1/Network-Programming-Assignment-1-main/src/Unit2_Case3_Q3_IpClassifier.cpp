// Unit 2, Case Study 3, Q3: IPv4 and IPv6 Classification

#include "common_net.hpp"
#include <iostream>
#include <string>

int main() {
    SocketSystem sockets;
    std::string value;
    while (true) {
        std::cout << "IP: ";
        std::getline(std::cin, value);
        if (value.empty()) break;

        sockaddr_in sa4{};
        sockaddr_in6 sa6{};
        if (inet_pton(AF_INET, value.c_str(), &sa4.sin_addr) == 1) {
            std::cout << value << " is IPv4" << std::endl;
        } else if (inet_pton(AF_INET6, value.c_str(), &sa6.sin6_addr) == 1) {
            std::cout << value << " is IPv6" << std::endl;
        } else {
            std::cout << value << " is invalid" << std::endl;
        }
    }
    return 0;
}
