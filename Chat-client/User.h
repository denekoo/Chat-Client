#pragma once

#include <iostream>
#include <string>
#include <vector>
class User
{
private:
    std::string m_userName;
    std::string m_password; // переделать в стринг!
    bool m_isAuthorized = false;
    bool m_activeUser = false;

public:
    User();
    User(std::string userName, std::string password);

    void setName(std::string name);
    void setPassword(std::string password);
    void setAuthStatus(bool auth);
    void setActiveUser(bool active);


    bool getActiveUser();
    std::string getUser();
    bool getAuthorized();
    std::string getPassword();

    void showUser();
    void defaultUser(std::string, std::string password);
};
