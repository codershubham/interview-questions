#pragma once

#include "Notification.h"
#include <memory>
#include <string>

class NotificationFactory {
public:
    // type: "email", "sms"
    static std::unique_ptr<Notification> create(const std::string& type) {
        if (type == "email") {
            return std::make_unique<EmailNotification>();
        } else if (type == "sms") {
            return std::make_unique<SMSNotification>();
        } else {
            return nullptr;
        }
    }
};

