#include <stdlib.h>
#include <iostream>
#include <string>

//#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "setup.h"
#include "login.h"

using std::cout;
using std::cin;


int main()
{
    using namespace sqlCon;
    

    setUp();
    int option{};
    do {
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "0. Exit\n\n";
     
        std::cout << "Enter your option: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
            registerUser();
            break;
        case 2:
            std::string username{};
            if(login(username))
            { 
                std::cout << username << '\n';
                int option{};
                
                do {
                    cout << "1. Check Balance\n";
                    cout << "2. Deposit\n";
                    cout << "3. Withdraw\n";
                    cout << "0. Exit\n\n";

                    std::cout << "Enter your option: ";
                    std::cin >> option;
                    std::string query;
                    sql::ResultSet* result;
                    switch (option)
                    {
                    case 1:
                        stmt = con->createStatement();
                        query = "Select balance FROM users WHERE username = '" + username + "'";
                        result = stmt->executeQuery(query);
                        if (result->next())
                        {
                            int balance = result->getInt("balance");
                            std::cout << "Balance: " << balance;
                        }
                        
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 0:
                        break;
                    default:
                        std::cout << "Invalid option.\n\n";
                    }
                } while (option != 0);
            }

            break;
        }
    } while (option != 0);

    delete con;
    return 0;
}