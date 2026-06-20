// Unit 3, Case Study 5, Q2: URL and URI Difference Demonstration

#include <iostream>
#include <regex>
#include <string>

int main() {
    std::regex url_pattern(R"(^[a-zA-Z][a-zA-Z0-9+.-]*://.+)");
    std::regex uri_pattern(R"(^[a-zA-Z][a-zA-Z0-9+.-]*:.+)");
    std::string input;

    while (true) {
        std::cout << "Input: ";
        std::getline(std::cin, input);
        if (input.empty()) break;

        if (std::regex_match(input, url_pattern)) {
            std::cout << "URL and also URI" << std::endl;
        } else if (std::regex_match(input, uri_pattern)) {
            std::cout << "URI but not URL" << std::endl;
        } else {
            std::cout << "Invalid URI/URL" << std::endl;
        }
    }
    return 0;
}
