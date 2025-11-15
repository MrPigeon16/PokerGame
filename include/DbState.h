#pragma once

#include <sqlite_modern_cpp.h>
class DbState {
    private:
    sqlite::database db;
    DbState();
public:
    static DbState& getInstance();
    sqlite::database& getConnection();
    void operator=(DbState& dbState) = delete;
    DbState(const DbState& dbState) = delete;
};
