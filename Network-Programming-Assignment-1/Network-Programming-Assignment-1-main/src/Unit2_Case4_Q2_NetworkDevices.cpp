// Unit 2, Case Study 4, Q2: Interface-Based Communication Simulation

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class NetworkDevice {
public:
    virtual void connect() = 0;
    virtual void sendData(const std::string& data) = 0;
    virtual void disconnect() = 0;
    virtual ~NetworkDevice() = default;
};

class EthernetDevice : public NetworkDevice {
public:
    void connect() override { std::cout << "Ethernet connected using cable" << std::endl; }
    void sendData(const std::string& data) override { std::cout << "Ethernet sending: " << data << std::endl; }
    void disconnect() override { std::cout << "Ethernet disconnected" << std::endl; }
};

class WiFiDevice : public NetworkDevice {
public:
    void connect() override { std::cout << "Wi-Fi connected using wireless signal" << std::endl; }
    void sendData(const std::string& data) override { std::cout << "Wi-Fi sending: " << data << std::endl; }
    void disconnect() override { std::cout << "Wi-Fi disconnected" << std::endl; }
};

int main() {
    std::vector<std::unique_ptr<NetworkDevice>> devices;
    devices.push_back(std::make_unique<EthernetDevice>());
    devices.push_back(std::make_unique<WiFiDevice>());

    for (auto& device : devices) {
        device->connect();
        device->sendData("Lab test message");
        device->disconnect();
        std::cout << std::endl;
    }
    return 0;
}
