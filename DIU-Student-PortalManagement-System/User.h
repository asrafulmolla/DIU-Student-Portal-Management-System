#ifndef USER_H
#define USER_H
#include<bits/stdc++.h>
using namespace std;
#include <string>

class User {
protected:
    string officialName;
    string username;
    string password;

public:
    User() {}
    User(const std::string &officialName, const std::string &username, const std::string &password)
        : officialName(officialName), username(username), password(password) {}

    virtual void registerUser() = 0;
    virtual bool loginUser(const std::string &username, const std::string &password) = 0;
};

#endif // USER_H
