#include <sqlite3.h>
#include <iostream>
#include <string>


const char* DB_FILE = "library.db";

const char* CREATE_TABLE_SQL = R"(
    CREATE TABLE IF NOT EXISTS books (
        id INTEGER PRIMARY KEY,
        title TEXT NOT NULL,
        author TEXT NOT NULL,
        publication_year INTEGER
    );
)";


int executeSQL(sqlite3* db, const std::string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    return rc;
}

int createTable(sqlite3* db) {
    return executeSQL(db, CREATE_TABLE_SQL);
}


int main() {
    sqlite3* db;
    int rc = sqlite3_open(DB_FILE, &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    rc = createTable(db);
    if (rc != SQLITE_OK) {
        std::cerr << "Error creating table." << std::endl;
        sqlite3_close(db);
        return 1;
    }

    std::cout << "Table created successfully." << std::endl;

    sqlite3_close(db);
    return 0;
}

