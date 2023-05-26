//#include <stdlib.h>
#include <iostream>
#include <vector>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;

//Connection iformation
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "12345";

namespace sqlCon{
    
    sql::Driver* driver;
    sql::Connection* con;
    sql::Statement* stmt;
    sql::PreparedStatement* pstmt;
}

void setUp()
{
    using namespace sqlCon;
    try
    {
        driver = get_driver_instance();
        con = driver->connect(server, username, password);
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    //Select the databse to work on
    con->setSchema("bank_manager");

    stmt = con->createStatement();
    //stmt->execute("DROP TABLE IF EXISTS users");  //Drop table if it already exists
    //stmt->execute("CREATE TABLE users (username VARCHAR(30) PRIMARY KEY, email VARCHAR(50), password VARCHAR(50),  balance INTEGER)");
    delete stmt;
}

void registerUser()
{
    using namespace sqlCon;
    std::string username{}, password{}, email{};
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    cout << "Email: ";
    cin >> email;

    stmt = con->createStatement();
    string selectQuery = "SELECT username FROM users";
    sql::ResultSet* usernames = stmt->executeQuery(selectQuery);  //Store the usernames 
  
    while (usernames->next())
    {
        if (username == usernames->getString("username"))  //Check to see if this useername already exists
        {
            cout << "Username is in use!\n";
            cout << "Would you like to enter another username(y/n)?\n";
            char choice{};
            cin >> choice;
            if (choice == 'y' || choice == 'Y')  //Enter new usernmae if previous is already in use
            {
                cout << "Username: ";
                cin >> username;
                usernames = stmt->executeQuery(selectQuery);  //reset usernames variable to check the new username
            }
            else
            {
                std::exit;
            }
        }
    }

    //Insert users info into the database
    stmt = con->createStatement();
    string insertQuery = "INSERT INTO users (username, password, email) VALUES "
           "('" + username + "', '" + password + "', '" + email + "')";
    stmt->execute(insertQuery);
    cout << "Registration Successful!/n";
    delete stmt;
}

int main()
{
    setUp();
    int option{};
    do {
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << '\n';
     
        std::cout << "Enter your option: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
            registerUser();
            break;
        case 2:

        }
    } while (option != 0);
    /*Check if table already exisst
    stmt->execute("SHOW TABLES LIKE 'users'");
    if (stmt->getResultSet()->next()) {
        cout << "Table 'users' already exists.\n" << endl;
    }
    else {
        cout << "Table 'inventory' does not exist." << endl;
    }
    */
   
    //cout << "Finished dropping table (if existed)" << endl;
    /*

    pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
    pstmt->setString(1, "banana");
    pstmt->setInt(2, 150);
    pstmt->execute();
    cout << "One row inserted." << endl;

    pstmt->setString(1, "orange");
    pstmt->setInt(2, 154);
    pstmt->execute();
    cout << "One row inserted." << endl;

    pstmt->setString(1, "apple");
    pstmt->setInt(2, 100);
    pstmt->execute();
    cout << "One row inserted." << endl;

    delete pstmt;
    delete con;
    system("pause");
    */
    return 0;
}