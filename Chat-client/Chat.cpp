#include "Chat.h"

Chat::Chat()
{ }

Chat::~Chat() {}

// главный метод, который вызывает вызывает все остальные
void Chat::chat_start()
{
    m_iclient.get_connect();// подключение к серверу
    registrator(); //вызов регистратора
    chat();



 }

void Chat::chat_stop()
{
   m_iclient.close_socket();
}

int Chat::numInput() // функция проверки ввода
{
    int num;
    bool f = true;
    while (f) {
        std::cout << "Enter your choice: \n" << std::endl;
        std::cin >> num;
        if (!std::cin) {
            std::cout << "It`s not a digit" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            f = true;
        } else
            f = false;
    }
    return num;
}

// Выбор действий с пользователем.
// Регистрация, вход и выход

void Chat::registrator()
{
    int choice = 0;
    std::cout << "Registrator." << std::endl;
    std::cout << "What do you want? \n";

    while (choice < 4)
    {
     std::cout << "Please choose the action: 1 - register, 2 - login, 3 - login out, 4 - exit from registrator  \n"
                  << std::endl;

        choice = numInput();

        switch (choice) {
        case 1: // register
        {
            if (regUser() == true)
            {
                std::cout << "User registred sucsefully!" << std::endl;
               // choice = 4;
            }
            else
            {
                std::cout << "User not register!" << std::endl;
            }
            break;
        }

        case 2: //login
        {
            if(logUser()) //добавить условия
            {
               // choice = 4;
            }
            break;
        }

        case 3: // logout
        {
          logOutUser();
            break;
        }

        case 4: // out of reg
        {
            choice = 4;
            break;
        }

        default:
        {
            std::cout << "Incorrect input!\n";
            break;
        }
    }
    std::cout << "Done!\n";
  }
}


std::string Chat::input_user_data() // ввод данных
{
    std::string user_data;
    std::cin >> user_data;
    return user_data;
}


bool Chat::checkUser(std::string user_login)
{
    std::string head = "check"; // для идентификации пакета
    std::string body;
    body.append(head.append(m_delim.append(user_login)));//trash (:

    m_iclient.send_data_to_serv(body); // отправка запроса на проверку пользователя
    std::string rec_serv = m_iclient.recip_mes_from_serv();
    if(rec_serv == "check_ok")
    {
    return true; // существует в базе
    }
    else if (rec_serv == "chek_no")
    {
        return false; // нет в базе
    }
    else
    {
        return false;
    }
}


 // регистратор пользователя
//  функция отправляет запрос на регистрацию на сервер.
// если пользователя не существует, то регистрируем.
// если пользователь уже зарегистирован, то предлагаем
// или рег с другим именем, или логин

bool Chat::regUser()
{
    std::cout << "Reg user. Enter your name:\n";
    std::string user_name = input_user_data();

    if(checkUser(user_name) == false) // false - такого пользователя не существует, можно регистрировать
    {
        //добавляем данные о пользователе
        m_user.setName(user_name);
        std::cout<< "Enter your password:\n";
        m_user.setPassword(input_user_data()); //добавить проверку и шифрование
        m_user.setActiveUser(true);
        m_user.setAuthStatus(true);
        //отправляем данные на сервер

        std::string head = "reg"; // для идентификации пакета
        std::string body = head + m_delim + m_user.getUser() + m_delim +  m_user.getPassword();

        m_iclient.send_data_to_serv(body); // отправка запроса на регистрацию
        std::string rec_serv = m_iclient.recip_mes_from_serv();

        // вывод информации о регистрации
        if(rec_serv == "reg_ok")
        {
            std::cout << "User " << m_user.getUser() << " registred! \n";
            return true;
        }
        else{
            std::cout << "Bad answer from server.";
            // что-то пошло не так
            return false;
        }
    }

    else
    {
        std::cout << "A user with name " << m_user.getUser() << "already exists! Choose another name or Login. \n ";
        return false;
    }
}


bool Chat::logUser()
{
     std::cout << "Login user. Enter your name:\n";
    std::string user_name = input_user_data();

    if(checkUser(user_name))
    {
        //добавляем данные о пользователе
        m_user.setName(user_name);
        std::cout<< "Enter your password:\n";
        m_user.setPassword(input_user_data()); //добавить проверку и шифрование
        m_user.setActiveUser(true);
        m_user.setAuthStatus(true);

        //отправляем данные на сервер
        std::string head = "log"; // для идентификации пакета
        std::string body = head + m_delim + m_user.getUser() + m_delim + m_user.getPassword();

         m_iclient.send_data_to_serv(body); // отправка запроса на вход
        std::string rec_serv =  m_iclient.recip_mes_from_serv();

        // вывод информации о регистрации
        if(rec_serv == "log_ok")
        {
            std::cout << "Welcome, " << m_user.getUser() <<! "\n";
            return true;
        }
        else{
            std::cout << "Bad answer from server.";
            // что-то пошло не так
            return false;
        }
    }
    return false;
}

void  Chat::logOutUser() // доработать
{
    m_user.setAuthStatus(false);
    std::string head = "log_offf"; // для идентификации пакета
    std::string body = head + m_delim + m_user.getUser();
    m_iclient.send_data_to_serv(body); // отправка запроса на выход
    std::string rec_serv =  m_iclient.recip_mes_from_serv();
}

Message Chat::send_message()
{

  std::string name = m_user.getUser();
  m_message.set_author(name);

  m_message.writeMessage();

  std::string message_to_send =  m_message.get_author() + m_delim +  m_message.get_message();
  m_iclient.send_data_to_serv(message_to_send);

  return m_message;
}

Message Chat::recip_message()
{
    std::string rec_serv =  m_iclient.recip_mes_from_serv();
    std::string name =str_subst_start(rec_serv);
    std::string mess = str_subst_end(rec_serv);

    Message msg(name, mess);
    return msg;
}

std::string Chat::str_subst_end(std::string mixed_string)
{
    size_t position = mixed_string.find(m_delim);
    size_t lenght = m_delim.size();
    std::string clear_string = mixed_string.substr(position+lenght, -1);
    return clear_string;
}


std::string Chat::str_subst_start(std::string mixed_string)
{
    //size_t position = mixed_string.find(m_delim);
    std::string clear_string = mixed_string.substr(0, mixed_string.find(m_delim));
    return clear_string;
}


void Chat::chat() // чат для общения пользователей
{
    std::cout<< "Let`s get start to chat!\n";
    std::cout<< "Send end to exit\n";
    std::string head_st = "chat_start"; // идентификатор для chat start

    m_iclient.send_data_to_serv(head_st); // отправка запроса на старт чата
    std::string rec_serv =  m_iclient.recip_mes_from_serv(); //ответ от сервера
     if(rec_serv == "chat_ok")
    {
        //m_user.showUser();
         bool work_chat = true;
         std::string end_waiting = "end";
         while (true)
        {
         m_message = send_message();
         m_messages.push_back(m_message); // отправляем сообщение и кладем его в массив сообщений

         if(m_message.get_message() == end_waiting)
             return;

         m_message = recip_message();  // получаем сообщение, показываем и кладем его в массив сообщений
         m_message.showMessage();
         m_messages.push_back(m_message);

         if(m_message.get_message() == end_waiting) // дубль, чтобы после каждого сообщ  выйти

             return;
         }
    }
    else
    {
         std::cout<< "closed";
         std::string head_end = "chat_end"; // идентификатор для chat end
         m_iclient.send_data_to_serv(head_end); // отправка запроса на старт чата
     }
 }






