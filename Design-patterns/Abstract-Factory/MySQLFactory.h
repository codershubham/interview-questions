#pragma once
#include "DB.h"
#include <iostream>

class MySQLConnection : public Connection {
public:
    void connect() override { std::cout << "[MySQL] Connected\n"; }
};

class MySQLCommand : public Command {
public:
    void execute(const std::string& sql) override { std::cout << "[MySQL] Execute: " << sql << '\n'; }
};

class MySQLTransaction : public Transaction {
public:
    void begin() override { std::cout << "[MySQL] Transaction begin\n"; }
    void commit() override { std::cout << "[MySQL] Transaction commit\n"; }
    void rollback() override { std::cout << "[MySQL] Transaction rollback\n"; }
};

class MySQLFactory : public DBFactory {
public:
    std::unique_ptr<Connection> createConnection() override { return std::make_unique<MySQLConnection>(); }
    std::unique_ptr<Command> createCommand() override { return std::make_unique<MySQLCommand>(); }
    std::unique_ptr<Transaction> createTransaction() override { return std::make_unique<MySQLTransaction>(); }
};