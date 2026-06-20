// Unit 3, Case Study 6, Q3: URL Encoder and Decoder

#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

std::string encode_url(const std::string& text) {
    std::ostringstream out;
    for (unsigned char c : text) {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            out << c;
        } else if (c == ' ') {
            out << '+';
        } else {
            out << '%' << std::uppercase << std::hex << std::setw(2) << std::setfill('0') << (int)c;
            out << std::nouppercase << std::dec;
        }
    }
    return out.str();
}

int hex_value(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return -1;
}

std::string decode_url(const std::string& text) {
    std::string out;
    for (std::size_t i = 0; i < text.size(); ++i) {
        if (text[i] == '+') out += ' ';
        else if (text[i] == '%' && i + 2 < text.size()) {
            int hi = hex_value(text[i + 1]);
            int lo = hex_value(text[i + 2]);
            if (hi >= 0 && lo >= 0) {
                out += static_cast<char>(hi * 16 + lo);
                i += 2;
            } else out += text[i];
        } else out += text[i];
    }
    return out;
}

int main() {
    std::string text;
    std::cout << "Text: ";
    std::getline(std::cin, text);

    std::string encoded = encode_url(text);
    std::string decoded = decode_url(encoded);

    std::cout << "Encoded: " << encoded << std::endl;
    std::cout << "Decoded: " << decoded << std::endl;
    return 0;
}
