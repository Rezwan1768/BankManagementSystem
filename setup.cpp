#include <iostream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "setup.h"

void setUp()
{
    using namespace sqlCon;
    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, user_name, password);
    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << '\n';
        std::exit(1);
    }

    //Select the databse to work on
    con->setSchema("bank_manager");

    stmt = con->createStatement();
    stmt->execute("DROP TABLE IF EXISTS users");  //Drop table if it already exists
    stmt->execute("CREATE TABLE users (username VARCHAR(30) PRIMARY KEY, email VARCHAR(50), password VARCHAR(50),  balance INTEGER DEFAULT 0)");
    delete stmt;
}