#include "inet_client.h"

IClient::IClient()
{ }

IClient::~IClient()
{ }


void IClient:: get_connect()
{
    // Создадим сокет
    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor == -1){
        std::cout << "Creation of Socket failed!" << std::endl;
        exit(1);
    }

    // Установим адрес сервера
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Зададим номер порта
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Установим соединение с сервером
    connection = connect(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    if(connection == -1){
        std::cout << "Connection with the server failed!" << std::endl;
        exit(1);
    }
}


void IClient:: send_data_to_serv(const std::string &datastr)
{
    //char *data;
    size_t data_size = datastr.size();
    //strcpy(data, datastr.c_str());
    strcpy(message, datastr.c_str());
    if ((strncmp(message, "end", 3)) == 0) {
        write(socket_file_descriptor, message, MESSAGE_LENGTH);
        std::cout << "Client Exit." << std::endl;
        return;
    }

    ssize_t bytes = write(socket_file_descriptor, message, data_size);
 // Если передали >= 0  байт, значит пересылка прошла успешно
    if(bytes >= 0){
        std::cout << "Data send to the server successfully.!" << std::endl;
    }
    bzero(message, MESSAGE_LENGTH);
}


std::string IClient::recip_mes_from_serv()
{
      bzero(message, MESSAGE_LENGTH);
    // Ждем ответа от сервера
    read(socket_file_descriptor, message, sizeof(message));
    std::cout << "Data received from server: " << message << std::endl;
    std::string received_message(message);
    return received_message;
}


void IClient::close_socket(){
    // закрываем сокет, завершаем соединение
   close(socket_file_descriptor);
}

