// Unit 3, Case Study 6, Q2: Password-Protected Page Simulation

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
        std::cout << "Welcome to internal portal." << std::endl;
        std::cout << "1. Lecture notes" << std::endl;
        std::cout << "2. Lab exercises" << std::endl;
        std::cout << "3. Assignment submissions" << std::endl;
    } else {
        std::cout << "Access denied." << std::endl;
    }
    return 0;
}
