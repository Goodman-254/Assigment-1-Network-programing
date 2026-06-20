// CPP 3204 Network Programming
// Unit 1, Case Study 1, Q1: Campus Helpdesk Client-Server System
// Compile Linux/macOS: g++ Unit1_Case1_Q1_Helpdesk.cpp -o Unit1_Case1_Q1_Helpdesk
// Compile Windows MinGW: g++ Unit1_Case1_Q1_Helpdesk.cpp -o Unit1_Case1_Q1_Helpdesk.exe -lws2_32
// Run server: ./Unit1_Case1_Q1_Helpdesk server
// Run client: ./Unit1_Case1_Q1_Helpdesk client

#include "common_net.hpp"
#include <iostream>
#include <string>

const int PORT = 5000;
const char* HOST = "127.0.0.1";

void run_server() {
    SocketSystem sockets;
    socket_t server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!socket_valid(server_fd)) {
        std::cerr << "Could not create server socket.\n";
        return;
    }

    int opt = 1;
#ifdef _WIN32
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&opt, sizeof(opt));
#else
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed. Port may already be in use.\n";
        close_socket(server_fd);
        return;
    }

    listen(server_fd, 5);
    std::cout << "Helpdesk server listening on port " << PORT << std::endl;

    int ticket = 1;
    while (true) {
        socket_t client_fd = accept(server_fd, nullptr, nullptr);
        if (!socket_valid(client_fd)) continue;

        std::string request = receive_text(client_fd);
        std::cout << "Received: " << request << std::endl;

        std::string ticket_no = "HD" + std::string(ticket < 10 ? "00" : ticket < 100 ? "0" : "") + std::to_string(ticket++);
        send_text(client_fd, "Request received. Ticket number: " + ticket_no);
        close_socket(client_fd);
    }
}

void run_client() {
    SocketSystem sockets;
    std::string reg, issue;
    std::cout << "Registration number: ";
    std::getline(std::cin, reg);
    std::cout << "Issue: ";
    std::getline(std::cin, issue);

    socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
    if (!socket_valid(sock)) {
        std::cerr << "Could not create client socket.\n";
        return;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, HOST, &server.sin_addr);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cout << "Server unreachable. Start the server first.\n";
        close_socket(sock);
        return;
    }

    send_text(sock, reg + ": " + issue);
    std::cout << receive_text(sock) << std::endl;
    close_socket(sock);
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "server") run_server();
    else run_client();
    return 0;
}
