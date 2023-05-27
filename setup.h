#ifndef SETUP_H
#define setup_H
#include "mysql_connection.h"


//Connection iformation
const std::string server = "tcp://127.0.0.1:3306";
const std::string user_name = "root";
const std::string password = "12345";


namespace sqlCon {

    inline sql::Driver* driver;
    inline sql::Connection* con;
    inline sql::Statement* stmt;
    inline sql::PreparedStatement* pstmt;
}

void setUp();
#endif 

