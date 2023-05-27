#ifndef LOGIN_H
#define LOGIN_H

bool userExists(const std::string& username);
void registerUser();
bool login();
#endif