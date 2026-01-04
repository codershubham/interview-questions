#include "MySQLFactory.h"
#include "PostgresFactory.h"
#include <iostream>
#include <memory>
#include <string>

int main(int argc, char** argv) {
    std::string backend = (argc > 1) ? argv[1] : "mysql"; // or "postgres"
    std::unique_ptr<DBFactory> factory;

    if (backend == "mysql") {
        factory = std::make_unique<MySQLFactory>();
    } else {
        factory = std::make_unique<PostgresFactory>();
    }

    auto conn = factory->createConnection();
    conn->connect();

    auto cmd = factory->createCommand();
    cmd->execute("SELECT * FROM users;");

    auto tx = factory->createTransaction();
    tx->begin();
    tx->commit();

    return 0;
}