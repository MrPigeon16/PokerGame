#include "DbState.h"
#include <sqlite_modern_cpp.h>

DbState::DbState() : db("../pokerdb.db"){
}

DbState& DbState::getInstance() {
    static DbState instance;
    return instance;
}

sqlite::database& DbState::getConnection() {
    return this->db;
}
