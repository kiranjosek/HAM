#ifndef IPPACK_H
#define IPPACK_H

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

class IPPack
{
public:
    char m_ip[64];
    int m_port;

    struct sockaddr_in m_socketAddress;
    int m_socketDescriptor;

    IPPack();
    IPPack(char * ip, int port);
    void SetIPPack(char* ip, int port);
    void Show();

    void SetSocketDescriptor(int sockfd);
    int  GetSocketDescriptor();

    int  IpEqual(struct sockaddr_in addr);
    void SetIp(struct sockaddr_in addr);
    void SetAddress(struct sockaddr_in addr);
    void GetAddress(struct sockaddr_in *sin);

};

#endif // IPPACK_H
