cmake_minimum_required(VERSION 3.5)

project(Chat-client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

 add_executable(Chat-client main.cpp
    User.cpp
    User.h
    Message.cpp
    Message.h
    Chat.cpp
    Chat.h
    inet_client.h
    inet_client.cpp)

include(GNUInstallDirs)
install(TARGETS Chat-client
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
