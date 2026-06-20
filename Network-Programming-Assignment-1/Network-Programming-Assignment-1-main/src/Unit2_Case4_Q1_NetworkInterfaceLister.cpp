// Unit 2, Case Study 4, Q1: List Network Interfaces

#include "common_net.hpp"
#include <cstdlib>
#include <iostream>

#ifndef _WIN32
#include <ifaddrs.h>
#endif

int main() {
    SocketSystem sockets;

#ifdef _WIN32
    std::cout << "Listing interfaces using Windows ipconfig command:\n\n";
    std::system("ipconfig /all");
#else
    ifaddrs* interfaces = nullptr;
    if (getifaddrs(&interfaces) != 0) {
        std::cout << "Unable to list network interfaces." << std::endl;
        return 1;
    }

    for (ifaddrs* p = interfaces; p != nullptr; p = p->ifa_next) {
        if (!p->ifa_addr) continue;
        int family = p->ifa_addr->sa_family;
        if (family == AF_INET || family == AF_INET6) {
            char addr[INET6_ADDRSTRLEN];
            void* src = family == AF_INET ?
                (void*)&((sockaddr_in*)p->ifa_addr)->sin_addr :
                (void*)&((sockaddr_in6*)p->ifa_addr)->sin6_addr;
            inet_ntop(family, src, addr, sizeof(addr));
            std::cout << "Interface name: " << p->ifa_name << std::endl;
            std::cout << "Display name: " << p->ifa_name << std::endl;
            std::cout << "IP Address: " << addr << std::endl;
            std::cout << "Active: yes if listed by the operating system" << std::endl;
            std::cout << "Multicast support: depends on interface configuration" << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }
    }
    freeifaddrs(interfaces);
#endif
    return 0;
}
