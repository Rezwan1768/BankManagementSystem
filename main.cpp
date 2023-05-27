#include <stdlib.h>
#include <iostream>
#include <vector>

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
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "0. Exit\n\n";
     
        std::cout << "Enter your option: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
            registerUser();
            break;
        case 2:
            if(login())
            { 
                int option{};
                
                do {
                    cout << "1. Check Balance\n";
                    cout << "2. Deposit\n";
                    cout << "3. Withdraw\n";
                    cout << "0. Exit\n\n";

                    std::cout << "Enter your option: ";
                    std::cin >> option;
                } while (option != 0);
            }

            break;
        }
    } while (option != 0);

    delete con;
    return 0;
}