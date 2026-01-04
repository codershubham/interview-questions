#pragma once
#include <memory>
#include <string>

struct Connection {
    virtual ~Connection() = default;
    virtual void connect() = 0;
};

struct Command {
    virtual ~Command() = default;
    virtual void execute(const std::string& sql) = 0;
};

struct Transaction {
    virtual ~Transaction() = default;
    virtual void begin() = 0;
    virtual void commit() = 0;
    virtual void rollback() = 0;
};

struct DBFactory {
    virtual ~DBFactory() = default;
    virtual std::unique_ptr<Connection> createConnection() = 0;
    virtual std::unique_ptr<Command> createCommand() = 0;
    virtual std::unique_ptr<Transaction> createTransaction() = 0;
};