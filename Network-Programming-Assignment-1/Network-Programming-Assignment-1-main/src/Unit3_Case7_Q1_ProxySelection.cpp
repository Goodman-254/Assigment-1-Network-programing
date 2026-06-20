// Unit 3, Case Study 7, Q1: Proxy Selection Simulation

#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::string extract_host(const std::string& url) {
    std::regex pattern(R"(^[a-zA-Z][a-zA-Z0-9+.-]*://([^/:?#]+))");
    std::smatch match;
    if (std::regex_search(url, match, pattern)) return match[1];
    return "";
}

bool contains_any(const std::string& text, const std::vector<std::string>& values) {
    for (const auto& v : values) if (text.find(v) != std::string::npos) return true;
    return false;
}

int main() {
    std::vector<std::string> local = {"localhost", "127.0.0.1", "jkuat.ac.ke"};
    std::vector<std::string> blocked = {"blockedsite.com", "malware.example"};

    std::string url;
    std::cout << "URL: ";
    std::getline(std::cin, url);

    std::string host = extract_host(url);
    if (host.empty()) std::cout << "Invalid URL" << std::endl;
    else if (contains_any(host, blocked)) std::cout << "Decision: Access denied" << std::endl;
    else if (contains_any(host, local) || host.size() >= 6 && host.substr(host.size() - 6) == ".local")
        std::cout << "Decision: Direct connection" << std::endl;
    else std::cout << "Decision: Use proxy" << std::endl;

    return 0;
}
