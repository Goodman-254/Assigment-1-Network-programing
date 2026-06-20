#ifndef COMMON_NET_HPP
#define COMMON_NET_HPP

#include <iostream>
#include <string>
#include <cstring>

#ifdef _WIN32
  #ifndef WIN32_LEAN_AND_MEAN
  #define WIN32_LEAN_AND_MEAN
  #endif
  #include <winsock2.h>
  #include <ws2tcpip.h>
  typedef SOCKET socket_t;
  inline void close_socket(socket_t s) { closesocket(s); }
  inline bool socket_valid(socket_t s) { return s != INVALID_SOCKET; }
  inline int socket_error_code() { return WSAGetLastError(); }
#else
  #include <arpa/inet.h>
  #include <netdb.h>
  #include <sys/socket.h>
  #include <sys/types.h>
  #include <unistd.h>
  typedef int socket_t;
  const int INVALID_SOCKET = -1;
  const int SOCKET_ERROR = -1;
  inline void close_socket(socket_t s) { close(s); }
  inline bool socket_valid(socket_t s) { return s >= 0; }
  inline int socket_error_code() { return errno; }
#endif

class SocketSystem {
public:
    SocketSystem() {
#ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "Failed to initialize Winsock\n";
        }
#endif
    }
    ~SocketSystem() {
#ifdef _WIN32
        WSACleanup();
#endif
    }
};

inline std::string receive_text(socket_t sock) {
    char buffer[2048];
    std::memset(buffer, 0, sizeof(buffer));
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes <= 0) return "";
    return std::string(buffer, bytes);
}

inline void send_text(socket_t sock, const std::string& text) {
    send(sock, text.c_str(), static_cast<int>(text.size()), 0);
}

#endif
