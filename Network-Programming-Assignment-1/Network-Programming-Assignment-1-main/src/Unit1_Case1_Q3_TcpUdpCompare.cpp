// Unit 1, Case Study 1, Q3: TCP and UDP Comparison
// Run: ./Unit1_Case1_Q3_TcpUdpCompare tcpserver | tcpclient | udpserver | udpclient

#include "common_net.hpp"
#include <iostream>
#include <string>

void tcp_server() {
    SocketSystem sockets;
    socket_t server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(6000);
    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    std::cout << "TCP server waiting on port 6000...\n";
    socket_t client = accept(server_fd, nullptr, nullptr);
    std::cout << "Received: " << receive_text(client) << std::endl;
    send_text(client, "TCP ACK: reliable connection");
    close_socket(client);
    close_socket(server_fd);
}

void tcp_client() {
    SocketSystem sockets;
    socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(6000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cout << "TCP server is not running.\n";
        close_socket(sock);
        return;
    }
    send_text(sock, "Hello through TCP");
    std::cout << receive_text(sock) << std::endl;
    close_socket(sock);
}

void udp_server() {
    SocketSystem sockets;
    socket_t sock = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(6001);
    bind(sock, (sockaddr*)&addr, sizeof(addr));
    std::cout << "UDP server waiting on port 6001...\n";

    char buffer[1024] = {0};
    sockaddr_in client{};
#ifdef _WIN32
    int len = sizeof(client);
#else
    socklen_t len = sizeof(client);
#endif
    int bytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&client, &len);
    std::cout << "Received: " << std::string(buffer, bytes) << std::endl;
    std::string reply = "UDP ACK: datagram received";
    sendto(sock, reply.c_str(), static_cast<int>(reply.size()), 0, (sockaddr*)&client, len);
    close_socket(sock);
}

void udp_client() {
    SocketSystem sockets;
    socket_t sock = socket(AF_INET, SOCK_DGRAM, 0);
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(6001);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
    std::string msg = "Hello through UDP";
    sendto(sock, msg.c_str(), static_cast<int>(msg.size()), 0, (sockaddr*)&server, sizeof(server));

    char buffer[1024] = {0};
    sockaddr_in from{};
#ifdef _WIN32
    int len = sizeof(from);
#else
    socklen_t len = sizeof(from);
#endif
    int bytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0, (sockaddr*)&from, &len);
    if (bytes > 0) std::cout << std::string(buffer, bytes) << std::endl;
    close_socket(sock);
}

int main(int argc, char* argv[]) {
    std::string mode = argc > 1 ? argv[1] : "help";
    if (mode == "tcpserver") tcp_server();
    else if (mode == "tcpclient") tcp_client();
    else if (mode == "udpserver") udp_server();
    else if (mode == "udpclient") udp_client();
    else {
        std::cout << "TCP uses connection-oriented reliable delivery.\n";
        std::cout << "UDP sends connectionless datagrams with lower overhead.\n";
        std::cout << "Use TCP for web, email and file transfer; use UDP for streaming, gaming and DNS.\n";
    }
    return 0;
}
