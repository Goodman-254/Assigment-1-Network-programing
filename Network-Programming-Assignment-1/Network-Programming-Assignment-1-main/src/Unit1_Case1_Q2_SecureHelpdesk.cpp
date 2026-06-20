// Unit 1, Case Study 1, Q2: Multiple Clients, Token Validation and Logging
// Run server: ./Unit1_Case1_Q2_SecureHelpdesk server
// Run client: ./Unit1_Case1_Q2_SecureHelpdesk client

#include "common_net.hpp"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>

const int PORT = 5001;
const std::string TOKEN = "NET123|";
std::mutex ticket_mutex;
int ticket_counter = 1;

std::string next_ticket() {
    std::lock_guard<std::mutex> lock(ticket_mutex);
    std::ostringstream out;
    out << "HD" << std::setw(3) << std::setfill('0') << ticket_counter++;
    return out.str();
}

std::string now_text() {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string s = std::ctime(&now);
    if (!s.empty() && s.back() == '\n') s.pop_back();
    return s;
}

void handle_client(socket_t client_fd) {
    std::string line = receive_text(client_fd);

    if (line.rfind(TOKEN, 0) != 0) {
        send_text(client_fd, "Rejected: invalid token");
        close_socket(client_fd);
        return;
    }

    std::string request = line.substr(TOKEN.size());
    if (request.size() < 5) {
        send_text(client_fd, "Rejected: message too short");
        close_socket(client_fd);
        return;
    }

    std::string ticket_no = next_ticket();
    std::ofstream log("helpdesk_log.txt", std::ios::app);
    log << now_text() << " " << ticket_no << " " << request << "\n";

    send_text(client_fd, "Accepted. Ticket: " + ticket_no);
    close_socket(client_fd);
}

void run_server() {
    SocketSystem sockets;
    socket_t server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!socket_valid(server_fd)) {
        std::cerr << "Could not create socket.\n";
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
        std::cerr << "Bind failed.\n";
        close_socket(server_fd);
        return;
    }

    listen(server_fd, 5);
    std::cout << "Secure helpdesk server listening on port " << PORT << std::endl;

    while (true) {
        socket_t client_fd = accept(server_fd, nullptr, nullptr);
        if (socket_valid(client_fd)) {
            std::thread(handle_client, client_fd).detach();
        }
    }
}

void run_client() {
    SocketSystem sockets;
    std::string request;
    std::cout << "Enter request message: ";
    std::getline(std::cin, request);

    socket_t sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        std::cout << "Server unreachable.\n";
        close_socket(sock);
        return;
    }

    send_text(sock, TOKEN + request);
    std::cout << receive_text(sock) << std::endl;
    close_socket(sock);
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "server") run_server();
    else run_client();
    return 0;
}
