// Unit 2, Case Study 3, Q2: Local Host Information

#include "common_net.hpp"
#include <iostream>
#include <string>

#ifndef _WIN32
#include <ifaddrs.h>
#endif

int main() {
    SocketSystem sockets;
    char hostname[256] = {0};
    gethostname(hostname, sizeof(hostname));
    std::cout << "Local host name: " << hostname << std::endl;

    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_UNSPEC;
    if (getaddrinfo(hostname, nullptr, &hints, &res) == 0) {
        for (addrinfo* p = res; p != nullptr; p = p->ai_next) {
            char ip[INET6_ADDRSTRLEN];
            void* addr = nullptr;
            if (p->ai_family == AF_INET) addr = &((sockaddr_in*)p->ai_addr)->sin_addr;
            else if (p->ai_family == AF_INET6) addr = &((sockaddr_in6*)p->ai_addr)->sin6_addr;
            else continue;
            inet_ntop(p->ai_family, addr, ip, sizeof(ip));
            std::cout << "Local IP: " << ip << std::endl;
        }
        freeaddrinfo(res);
    }

#ifdef _WIN32
    std::cout << "\nWindows interface details can be viewed using: ipconfig /all\n";
    std::system("ipconfig /all");
#else
    ifaddrs* interfaces = nullptr;
    if (getifaddrs(&interfaces) == 0) {
        for (ifaddrs* p = interfaces; p != nullptr; p = p->ifa_next) {
            if (!p->ifa_addr) continue;
            int family = p->ifa_addr->sa_family;
            if (family == AF_INET || family == AF_INET6) {
                char addr[INET6_ADDRSTRLEN];
                void* src = family == AF_INET ?
                    (void*)&((sockaddr_in*)p->ifa_addr)->sin_addr :
                    (void*)&((sockaddr_in6*)p->ifa_addr)->sin6_addr;
                inet_ntop(family, src, addr, sizeof(addr));
                std::cout << "Interface: " << p->ifa_name << " Address: " << addr << std::endl;
            }
        }
        freeifaddrs(interfaces);
    }
#endif
    return 0;
}
