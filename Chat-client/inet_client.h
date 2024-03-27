#pragma once

#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define MESSAGE_LENGTH 1024 // Максимальный размер буфера для данных
#define PORT 7777 // Будем использовать этот номер порта

class IClient {
private:
    int socket_file_descriptor, connection;
    struct sockaddr_in serveraddress, client;
    char message[MESSAGE_LENGTH];

public:
    IClient();
    ~IClient();

    void get_connect();
    void send_data_to_serv(/*char* data, int data_size*/const std::string &datastr);
    std::string recip_mes_from_serv();
    void  close_socket();

};
