#pragma once
#include <iostream>
#include <string>

class Message
{
private:
    // реквизиты отправаителя:
    std::string m_messageAuthor;

    //тело сообщения:
    std::string m_message;

public:
    Message(std::string &messageAuthor, std::string &message);
    Message(std::string messageAuthor);
    Message();

    void set_author(std::string author);
    void set_message(std::string msg_text);

    std::string get_author();
    std::string get_message();

    void writeMessage();
    void showMessage();
};
