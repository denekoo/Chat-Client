#include "User.h"

User::User() {}

User::User(std::string userName, std::string password)
    : m_userName(userName)
    , m_password(password)
{}

void User::setName(std::string name)
{
    m_userName = name;
}
void User::setPassword(std::string password)
{
    m_password = password;
}
void User::setAuthStatus(bool auth)
{
    m_isAuthorized = auth;
}
void User::setActiveUser(bool active)
{
    m_activeUser = active;
}

std::string User::getUser()
{
    return m_userName;
}
bool User::getActiveUser()
{
    return m_activeUser;
}
bool User::getAuthorized()
{
    return m_isAuthorized;
}
std::string User::getPassword()
{
    return m_password;
}

void User::showUser()
{
    std::cout << "User " << m_userName << " joined to chat." << std::endl;
    std::cout << "User pass " << m_password  << std::endl;
    std::cout << "User is authorized: " << m_isAuthorized << std::endl;
    std::cout << "User is active: " << m_activeUser << std::endl;

}
void User::defaultUser(std::string, std::string password)
{
    m_userName = "default"; //
    m_password = "0000";
    m_isAuthorized = true;
}
