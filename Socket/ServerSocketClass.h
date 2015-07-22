#ifndef SERVERSOCKETCLASS_H
#define SERVERSOCKETCLASS_H

#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "SocketBase.h"

#define MAXPENDING 16

class ServerSocketClass : public SocketBase
{
public:
    ServerSocketClass();
    int CreateServerSocket(int port);

};

#endif // SERVERSOCKETCLASS_H
