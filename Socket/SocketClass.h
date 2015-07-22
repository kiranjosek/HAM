#ifndef SOCKETCLASS_H
#define SOCKETCLASS_H
#include "ServerSocketClass.h"
#include "ClientSocketClass.h"

class SocketClass: public SocketBase//: virtual public ServerSocketClass, public ClientSocketClass
{

public:
    SocketClass();

    int CreateSocket(int port,char* ip = NULL);
    int CreateServerSocket(int port);
    int CreateClientSocket(char* ip,int port);
    int CreateClientSocket(char* server, int port, int timeout);

};

#endif // SOCKETCLASS_H
