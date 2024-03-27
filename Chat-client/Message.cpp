#include "Message.h"



Message::Message(std::string &messageAuthor, std::string &message):
    m_messageAuthor(messageAuthor),
     m_message(message)
{}

Message::Message(std::string author): m_messageAuthor(author)
{ }


Message::Message()
{
    m_messageAuthor = "Default";

}


void Message::set_author(std::string author)
{
    m_messageAuthor = author;
}
void Message:: set_message(std::string msg_text)
{

}

void Message::writeMessage()
{
    std::cout << "Write your message: \n";
    std::getline(std::cin, m_message, '\n');
}
std::string Message::get_author()
{
    return m_messageAuthor;

}

std::string Message::get_message()
{
    return m_message;
}


void Message::showMessage()
{
    std::cout << "\t\t\t\t"
              << "User " << m_messageAuthor << " send to chat:\n";
    std::cout << "\t\t\t\t" << m_message << std::endl;
    std::cout << "\t\t\t\t"
              << "---------" << std::endl;
 }

