// Unit 2, Case Study 3, Q1: Hostname and IP Resolver

#include "common_net.hpp"
#include <iostream>
#include <set>
#include <string>

int main() {
    SocketSystem sockets;
    std::string domain;
    std::cout << "Enter domain: ";
    std::getline(std::cin, domain);

    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(domain.c_str(), nullptr, &hints, &res) != 0) {
        std::cout << "Host cannot be resolved." << std::endl;
        return 1;
    }

    std::set<std::string> seen;
    for (addrinfo* p = res; p != nullptr; p = p->ai_next) {
        char ip[INET6_ADDRSTRLEN];
        void* addr = nullptr;
        std::string type;

        if (p->ai_family == AF_INET) {
            addr = &((sockaddr_in*)p->ai_addr)->sin_addr;
            type = "IPv4";
        } else if (p->ai_family == AF_INET6) {
            addr = &((sockaddr_in6*)p->ai_addr)->sin6_addr;
            type = "IPv6";
        } else continue;

        inet_ntop(p->ai_family, addr, ip, sizeof(ip));
        if (seen.insert(ip).second) {
            std::cout << "Host: " << domain << " IP: " << ip << " Type: " << type << std::endl;
        }
    }
    freeaddrinfo(res);
    return 0;
}
