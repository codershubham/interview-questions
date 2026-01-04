#include "Factory.h"
#include <iostream>

int main() {
    auto email = NotificationFactory::create("email");
    if (email) email->send("alice@example.com", "Welcome!");

    auto sms = NotificationFactory::create("sms");
    if (sms) sms->send("+1234567890", "Your code is 1234");

    // unknown type -> nullptr
    auto unknown = NotificationFactory::create("push");
    if (!unknown) std::cout << "Unknown notification type\n";

    return 0;
}