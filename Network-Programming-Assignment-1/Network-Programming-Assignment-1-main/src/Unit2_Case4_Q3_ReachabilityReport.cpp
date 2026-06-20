// Unit 2, Case Study 4, Q3: Reachability Testing Tool with Text Report

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> hosts;
    std::string host;

    while (true) {
        std::cout << "Host: ";
        std::getline(std::cin, host);
        if (host.empty()) break;
        hosts.push_back(host);
    }

    std::ofstream report("reachability_report.txt");
    report << "Reachability Report\n";
    report << "===================\n\n";

    for (const std::string& h : hosts) {
        auto start = std::chrono::steady_clock::now();
#ifdef _WIN32
        std::string command = "ping -n 1 " + h + " > nul 2>&1";
#else
        std::string command = "ping -c 1 " + h + " > /dev/null 2>&1";
#endif
        int result = std::system(command.c_str());
        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        report << "Host: " << h << "\n";
        report << "Status: " << (result == 0 ? "Reachable" : "Unreachable") << "\n";
        report << "Response time: " << ms << " ms\n\n";
    }

    report.close();
    std::cout << "Report saved as reachability_report.txt" << std::endl;
    return 0;
}
