// Unit 3, Case Study 5, Q3: Relative URL Resolver

#include <iostream>
#include <string>

int main() {
    std::string base, relative;
    std::cout << "Base URL: ";
    std::getline(std::cin, base);
    std::cout << "Relative URL: ";
    std::getline(std::cin, relative);

    if (relative.rfind("http://", 0) == 0 || relative.rfind("https://", 0) == 0) {
        std::cout << "Absolute URL: " << relative << std::endl;
    } else if (!relative.empty() && relative[0] == '/') {
        std::size_t scheme_end = base.find("://");
        if (scheme_end != std::string::npos) {
            std::size_t host_end = base.find('/', scheme_end + 3);
            std::string root = host_end == std::string::npos ? base : base.substr(0, host_end);
            std::cout << "Absolute URL: " << root << relative << std::endl;
        } else {
            std::cout << "Invalid base URL" << std::endl;
        }
    } else {
        if (!base.empty() && base.back() != '/') base += "/";
        std::cout << "Absolute URL: " << base << relative << std::endl;
    }
    return 0;
}
