#include "IPPack.h"
#include <string.h>
#include <stdio.h>

IPPack::IPPack()
{
    memset(m_ip,'\0',64);
    m_port = -1;
    m_socketDescriptor = -1;
}

IPPack::IPPack(char * ip, int port)
{
    memset(m_ip,'\0',64);
    SetIPPack(ip,port);
}

void IPPack::SetIPPack(char* ip, int port)
{
    if(ip)
        memcpy(m_ip,ip,strlen(ip)+1);

    m_port = port;
}

void IPPack::Show()
{
    printf("IPPack: IP-> %s PORT->%d\n",m_ip,m_port);
}


void IPPack::SetSocketDescriptor(int sockfd)
{
    m_socketDescriptor = sockfd;
}

int IPPack::GetSocketDescriptor()
{
    return m_socketDescriptor;
}

void IPPack::GetAddress(struct sockaddr_in *sin)
{
    memcpy(sin,&m_socketAddress,sizeof(struct sockaddr_in));
}

void IPPack::SetIp(struct sockaddr_in addr)
{
    memcpy(&m_socketAddress.sin_addr,&addr.sin_addr,sizeof(struct in_addr));
}

void IPPack::SetAddress(struct sockaddr_in addr)
{
    memcpy(&m_socketAddress,&addr,sizeof(struct sockaddr_in));
}

int IPPack::IpEqual(struct sockaddr_in addr)
{
    fprintf(stdout,"IpEquiv: %s <=> ", inet_ntoa(m_socketAddress.sin_addr));
    fprintf(stdout,"%s\n", inet_ntoa(addr.sin_addr));
    return (memcmp(&m_socketAddress.sin_addr,&addr.sin_addr,sizeof(struct in_addr)) == 0) ? 1 : 0;
}
