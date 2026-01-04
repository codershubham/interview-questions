#pragma once
#include "DB.h"
#include <iostream>

class PostgresConnection : public Connection {
public:
    void connect() override { std::cout << "[Postgres] Connected\n"; }
};

class PostgresCommand : public Command {
public:
    void execute(const std::string& sql) override { std::cout << "[Postgres] Execute: " << sql << '\n'; }
};

class PostgresTransaction : public Transaction {
public:
    void begin() override { std::cout << "[Postgres] Transaction begin\n"; }
    void commit() override { std::cout << "[Postgres] Transaction commit\n"; }
    void rollback() override { std::cout << "[Postgres] Transaction rollback\n"; }
};

class PostgresFactory : public DBFactory {
public:
    std::unique_ptr<Connection> createConnection() override { return std::make_unique<PostgresConnection>(); }
    std::unique_ptr<Command> createCommand() override { return std::make_unique<PostgresCommand>(); }
    std::unique_ptr<Transaction> createTransaction() override { return std::make_unique<PostgresTransaction>(); }
};