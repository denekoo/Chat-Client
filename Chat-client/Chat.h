#pragma once

#include "Message.h"
#include "User.h"
#include"inet_client.h"


#include <ios> //used to get stream size
#include <iostream>
#include <limits> //used to get numeric limits
#include <vector>
//клиент:
// рег польз, логин, выход
// набор, отправка сообщ, прием сообщ.
// выбор комнаты и собеседника

//сервер
// хранение польз, авторизация
// беседы: общая и личная
// прием сообщ
// отправка принятых сообщ клиенту


class Chat
{
private:

    std::vector<Message> m_messages;
    int m_messagesCount = 0;
    User m_user;
    Message m_message;
    IClient m_iclient;
    std::string m_delim = "|+|";


public:
    Chat();
    ~Chat();

    void chat_start(); // старт работы программы
    void chat_stop();
    int numInput(); // Функция проверки ввода, с защитой от некорректного ввода
    void registrator(); // Регисратор, выполняет все функции по регистрации и входу пользователей

    //клиент:
     std::string input_user_data();

    bool checkUser(std::string user_login);   // проверка существования пользователя на сервере
    //bool checkPassword(User user, int password);
    bool regUser();                  // регистратор пользователя

    bool logUser();                  // вход
    void logOutUser();               // выход

    bool chatMessage(User user); // Функция отправки сообщения от выбранного пользователя

    Message send_message();
    Message recip_message();

    std::string str_subst_end(std::string mixed_string); // возвращает строку после идентификатора типа запроса по разделителю delim
    std::string str_subst_start(std::string mixed_string); // возвращает строку до идентификатора типа запроса по разделителю delin


    void chat(); //  чат для общения пользователей



};
