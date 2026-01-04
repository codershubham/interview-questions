#pragma once

#include <string>
#include <iostream>
#include <memory>

class Notification {
public:
    virtual ~Notification() = default;
    virtual void send(const std::string& to, const std::string& message) = 0;
};

// Concrete products (kept simple for demonstration)
class EmailNotification : public Notification {
public:
    void send(const std::string& to, const std::string& message) override {
        std::cout << "[Email] To: " << to << " Msg: " << message << '\n';
    }
};

class SMSNotification : public Notification {
public:
    void send(const std::string& to, const std::string& message) override {
        std::cout << "[SMS] To: " << to << " Msg: " << message << '\n';
    }
};