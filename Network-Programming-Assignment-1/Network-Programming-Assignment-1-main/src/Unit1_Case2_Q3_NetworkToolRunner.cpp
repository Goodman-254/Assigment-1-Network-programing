// Unit 1, Case Study 2, Q3: Tool-Based Report Command Runner

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool command_exists(const std::string& command) {
#ifdef _WIN32
    std::string check = "where " + command + " > nul 2>&1";
#else
    std::string check = "command -v " + command + " > /dev/null 2>&1";
#endif
    return std::system(check.c_str()) == 0;
}

int main() {
    std::ofstream report("tool_report.txt");
    report << "Network Tool Report\n";
    report << "===================\n";
    report.close();

#ifdef _WIN32
    std::vector<std::pair<std::string, std::string>> tools = {
        {"ping", "ping -n 4 8.8.8.8 >> tool_report.txt 2>&1"},
        {"netstat", "netstat -an >> tool_report.txt 2>&1"},
        {"nmap", "nmap -F 127.0.0.1 >> tool_report.txt 2>&1"},
        {"iperf3", "iperf3 --version >> tool_report.txt 2>&1"}
    };
#else
    std::vector<std::pair<std::string, std::string>> tools = {
        {"ping", "ping -c 4 8.8.8.8 >> tool_report.txt 2>&1"},
        {"netstat", "netstat -an >> tool_report.txt 2>&1"},
        {"nmap", "nmap -F 127.0.0.1 >> tool_report.txt 2>&1"},
        {"iperf3", "iperf3 --version >> tool_report.txt 2>&1"}
    };
#endif

    for (const auto& tool : tools) {
        std::ofstream out("tool_report.txt", std::ios::app);
        out << "\n===== " << tool.first << " =====\n";
        out.close();

        if (command_exists(tool.first)) {
            std::system(tool.second.c_str());
        } else {
            std::ofstream missing("tool_report.txt", std::ios::app);
            missing << tool.first << " is not installed.\n";
        }
    }

    std::cout << "Tool report saved as tool_report.txt" << std::endl;
    return 0;
}
