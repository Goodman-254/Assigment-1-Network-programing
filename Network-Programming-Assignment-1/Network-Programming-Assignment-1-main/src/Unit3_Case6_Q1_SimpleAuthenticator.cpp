// Unit 3, Case Study 6, Q1: Simple Authenticator Program

#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, std::string> users = {
        {"admin", "admin123"},
        {"student", "net2026"},
        {"lecturer", "teach456"}
    };

    std::string username, password;
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);

    if (users.count(username) && users[username] == password) {
        std::cout << "Authentication successful" << std::endl;
    } else {
        std::cout << "Authentication failed" << std::endl;
    }
    return 0;
}
