// Unit 1, Case Study 2, Q2: Port Availability Scanner

#include "common_net.hpp"
#include <iostream>
#include <string>
#include <vector>

bool check_port(const std::string& host, int port) {
    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    std::string port_text = std::to_string(port);
    if (getaddrinfo(host.c_str(), port_text.c_str(), &hints, &res) != 0) return false;

    bool open = false;
    for (addrinfo* p = res; p != nullptr; p = p->ai_next) {
        socket_t sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (!socket_valid(sock)) continue;
        if (connect(sock, p->ai_addr, static_cast<int>(p->ai_addrlen)) == 0) open = true;
        close_socket(sock);
        if (open) break;
    }
    freeaddrinfo(res);
    return open;
}

int main() {
    SocketSystem sockets;
    std::string host;
    std::cout << "Enter host or IP: ";
    std::getline(std::cin, host);

    std::vector<std::pair<int, std::string>> ports = {
        {21, "FTP"}, {22, "SSH"}, {25, "SMTP"}, {53, "DNS"}, {80, "HTTP"}, {443, "HTTPS"}
    };

    for (const auto& item : ports) {
        std::cout << "Port " << item.first << " (" << item.second << ") is "
                  << (check_port(host, item.first) ? "open" : "closed") << std::endl;
    }
    return 0;
}
