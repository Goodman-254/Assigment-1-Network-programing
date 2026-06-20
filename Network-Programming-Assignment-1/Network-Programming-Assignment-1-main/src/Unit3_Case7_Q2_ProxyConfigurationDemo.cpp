// Unit 3, Case Study 7, Q2: Proxy Configuration Program

#include <iostream>
#include <string>

int main() {
    std::string proxy_host, target_url;
    int proxy_port;

    std::cout << "Proxy host: ";
    std::getline(std::cin, proxy_host);
    std::cout << "Proxy port: ";
    std::cin >> proxy_port;
    std::cin.ignore();
    std::cout << "Target URL: ";
    std::getline(std::cin, target_url);

    std::cout << "Connecting to " << target_url << " through "
              << proxy_host << ":" << proxy_port << std::endl;
    return 0;
}
