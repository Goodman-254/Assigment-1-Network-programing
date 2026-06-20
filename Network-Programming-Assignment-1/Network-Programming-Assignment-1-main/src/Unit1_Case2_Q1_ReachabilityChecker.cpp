// Unit 1, Case Study 2, Q1: Network Reachability Checker

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>

int main() {
    std::string host;
    std::cout << "Enter hostname or IP: ";
    std::getline(std::cin, host);

    auto start = std::chrono::steady_clock::now();
#ifdef _WIN32
    std::string command = "ping -n 1 " + host + " > nul 2>&1";
#else
    std::string command = "ping -c 1 " + host + " > /dev/null 2>&1";
#endif
    int result = std::system(command.c_str());
    auto end = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Host: " << host << std::endl;
    std::cout << "Reachable: " << (result == 0 ? "true" : "false") << std::endl;
    std::cout << "Time taken: " << ms << " ms" << std::endl;
    return 0;
}
