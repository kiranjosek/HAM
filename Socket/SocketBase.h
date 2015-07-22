#ifndef SOCKETBASE_H
#define SOCKETBASE_H


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

#include "IPPack.h"

enum SOCKET_TYPE { SOCKET_NONE, SOCKET_CLIENT, SOCKET_SERVER };

class SocketBase
{

protected:
    struct sockaddr_in m_socketAddress;
    int m_socketDescriptor;
    struct IPPack m_IPSet;
    SOCKET_TYPE m_socketType;

public:
    SocketBase();

    void SetSocketDescriptor(int sockfd);
    int  GetSocketDescriptor();

    int  IpEqual(struct sockaddr_in addr);
    void SetIp(struct sockaddr_in addr);
    void SetAddress(struct sockaddr_in addr);
    void GetAddress(struct sockaddr_in *sin);
    int SetSocketFlags(int sock,int newFlag);

    long BytesAvailable();
    int ResolveHostName(const char* hostname, struct in_addr* addr);
    bool WaitForReadEvent(int timeoutInSec);

};

#endif // SOCKETBASE_H
