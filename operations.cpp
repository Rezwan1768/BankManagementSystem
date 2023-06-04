#include <iostream>
#include <string>

#include <cppconn/prepared_statement.h>
#include "setup.h"
#include "login.h"
#include "operations.h"


int getBalance(std::string& username)
{
	using namespace sqlCon;
	stmt = con->createStatement();
    int balance{};
    sql::ResultSet* result = stmt->executeQuery("Select balance FROM users WHERE username = '" + username + "'");
    if (result->next())
    {
        balance = result->getInt("balance");
    }

    delete stmt;
    delete result;
    return balance;
}

void deposit(std::string& username)
{
    using namespace sqlCon;
    int value{};
    std::cout << "Enter Deposit amount: ";
    std::cin >> value;
    pstmt = con->prepareStatement("UPDATE users SET balance = balance + ? WHERE username = ?");
    pstmt->setInt(1, value); // Set the value to add to the balance
    pstmt->setString(2, username); // Set the username
    pstmt->executeUpdate();
    std::cout << "Your new balance is: " << getBalance(username) << "\n\n";
    delete pstmt;
}

void withdrawl(std::string& username)
{
    using namespace sqlCon;
    int value{};
    std::cout << "Enter Withdral amount: ";
    std::cin >> value;
    if ((getBalance(username) - value) >= 0)
    {
        pstmt = con->prepareStatement("UPDATE users SET balance = balance - ? WHERE username = ?");
        pstmt->setInt(1, value);
        pstmt->setString(2, username);
        pstmt->executeUpdate();
        std::cout << "Your new balance is: " << getBalance(username) << "\n\n";
        delete pstmt;
    }
    else
    {
        std::cout << "You dont have enough balnce to make this withdrawl.\n";
        std::cout << "Your current balance is: " << getBalance(username) << "\n\n";
    }
}
