// Unit 3, Case Study 5, Q1: URL Component Extractor

#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string url;
    std::cout << "Enter URL: ";
    std::getline(std::cin, url);

    std::regex pattern(R"(^([a-zA-Z][a-zA-Z0-9+.-]*)://([^/:?#]+)(:([0-9]+))?([^?#]*)(\?([^#]*))?(#(.*))?$)");
    std::smatch match;

    if (std::regex_match(url, match, pattern)) {
        std::cout << "Protocol: " << match[1] << std::endl;
        std::cout << "Host: " << match[2] << std::endl;
        std::cout << "Port: " << (match[4].matched ? match[4].str() : "Default") << std::endl;
        std::cout << "Path: " << match[5] << std::endl;
        std::cout << "Query: " << match[7] << std::endl;
        std::cout << "Fragment: " << match[9] << std::endl;
    } else {
        std::cout << "Invalid URL" << std::endl;
    }
    return 0;
}
