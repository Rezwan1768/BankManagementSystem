#include <stdlib.h>
#include <iostream>
#include <string>

//#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "setup.h"
#include "login.h"
#include "operations.h"

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
        std::string username;
        switch (option)
        {
        case 1:
            registerUser();
            break;
        case 2:
            if(login(username))
            { 
                int option{};
                
                do {
                    cout << "1. Check Balance\n";
                    cout << "2. Deposit\n";
                    cout << "3. Withdraw\n";
                    cout << "0. Exit\n\n";

                    std::cout << "Enter your option: ";
                    std::cin >> option;
                    int value{};
                    switch (option)
                    {
                    case 1:
                        std::cout << "Your Balance: " << getBalance(username) << "\n\n";
                        break;
                    case 2:
                        deposit(username);
                        break;
                    case 3:
                        withdrawl(username);
                        break;
                    case 0:
                        break;
                    default:
                        std::cout << "Invalid option.\n\n";
                    }
                } while (option != 0);
            }
            break;
        default:
            std::cout << "Invalid option.\n\n";
        }
    } while (option != 0);

    delete con;
    return 0;
}