#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "setup.h"
#include "login.h"

using std::cout;
using std::cin;

//Check if username already exists
bool userExists(const std::string& username)
{
    sqlCon::stmt = sqlCon::con->createStatement();
    sql::ResultSet* usernames = sqlCon::stmt->executeQuery("SELECT username FROM users");  //Store the usernames 
    while (usernames->next())
    {
        if (username == usernames->getString("username"))  //if this useername already exists
        {
            return true;
        }
    }
    delete sqlCon::stmt;
    return false;
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
    cout << '\n';
    while (userExists(username))
    {
        cout << "Username is in use!\n";
        cout << "Would you like to enter another username(y/n)?\n";
        char choice{};
        cin >> choice;
        if (choice == 'y' || choice == 'Y')  //Enter new username if previous is already in use
        {
            cout << "Username: ";
            cin >> username;
        }
        else
        {
            return;
        }
        cout << "\n\n";
    }

    //Insert users info into the database
    stmt = con->createStatement();
    std::string insertQuery = "INSERT INTO users (username, password, email) VALUES "
        "('" + username + "', '" + password + "', '" + email + "')";
    stmt->execute(insertQuery);
    cout << "Registration Successful!\n";
    delete stmt;
}

bool login(std::string& username)
{
    using namespace sqlCon;
    std::string password{};
    cout << "Username: ";
    std::cin >> username;
    cout << "Password: ";
    std::cin >> password;

    stmt = con->createStatement();
    std::string selectQuery = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "'";
    sql::ResultSet* result = stmt->executeQuery(selectQuery); //look for matching values
    if (result->next())  //if resultset has any values
    {
        std::system("CLS"); //Clear screen 
        cout << "Authentication successful. Username and password match.\n\n";
        delete result;
        delete stmt;
        return true;
    }
    else {
        cout << "Authentication failed. Username and password do not match.\n\n";
        delete result;
        delete stmt;
        return false;
    }
}

