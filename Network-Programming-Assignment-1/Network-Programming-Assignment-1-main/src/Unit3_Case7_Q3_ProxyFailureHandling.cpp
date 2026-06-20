// Unit 3, Case Study 7, Q3: Proxy Failure Handling

#include <iostream>
#include <string>

int main() {
    std::string host, port_text, url;
    int port = -1;

    std::cout << "Proxy host: ";
    std::getline(std::cin, host);
    std::cout << "Proxy port: ";
    std::getline(std::cin, port_text);
    std::cout << "URL: ";
    std::getline(std::cin, url);

    try {
        port = std::stoi(port_text);
    } catch (...) {
        port = -1;
    }

    if (host.empty()) {
        std::cout << "Error: proxy host cannot be empty" << std::endl;
    } else if (port <= 0 || port > 65535) {
        std::cout << "Error: invalid port" << std::endl;
    } else if (!(url.rfind("http://", 0) == 0 || url.rfind("https://", 0) == 0)) {
        std::cout << "Error: invalid URL" << std::endl;
    } else if (url.find("blockedsite.com") != std::string::npos) {
        std::cout << "Error: blocked website" << std::endl;
    } else {
        std::cout << "Proxy settings accepted" << std::endl;
    }
    return 0;
}
