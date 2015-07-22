#ifndef CLIENTSOCKETCLASS_H
#define CLIENTSOCKETCLASS_H

#include <stdio.h>
#include <error.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "SocketBase.h"

class ClientSocketClass :public SocketBase
{
public:
    ClientSocketClass();
    int CreateClientSocket(char* ip,int port);

};

#endif // CLIENTSOCKETCLASS_H
