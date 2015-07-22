#include "SocketBase.h"
#include <netdb.h>

SocketBase::SocketBase()
{
    m_socketType = SOCKET_NONE;
    m_socketDescriptor = -1;
}

void SocketBase::SetSocketDescriptor(int sockfd)
{
    printf("SetSocketDescriptor(%d);\n",sockfd);
    m_socketDescriptor = sockfd;
    m_socketType = SOCKET_NONE;

    char ipstr[INET6_ADDRSTRLEN];
    memset(ipstr,0,INET6_ADDRSTRLEN);
    int port = -1;

    int val;
    socklen_t len = sizeof val;

    if(getsockopt(sockfd,SOL_SOCKET,SO_ACCEPTCONN,&val,&len) == -1)
    {
        printf("Its not a socket\n");
    }
    else if(val)
    {
        m_socketType = SOCKET_SERVER;
        printf("Its a listening Socket\n");
        len = sizeof(m_socketAddress);

        if(getsockname(m_socketDescriptor,(struct sockaddr*)&m_socketAddress,&len) < 0)
        {
            perror("getsockname");
        }
        else
        {
            inet_ntop(AF_INET, &m_socketAddress.sin_addr, ipstr, sizeof ipstr);
            port = ntohs(m_socketAddress.sin_port);
        }
    }
    else
    {
        m_socketType = SOCKET_CLIENT;
        printf("Its a client Socket\n");
        struct sockaddr_storage addr;
        len = sizeof addr;
        if(getpeername(m_socketDescriptor, (struct sockaddr*)&addr, &len) == 0)
        {
            if (addr.ss_family == AF_INET)
            {
                struct sockaddr_in *s = (struct sockaddr_in *)&addr;
                memcpy(&m_socketAddress,s,sizeof(m_socketAddress));
                port = ntohs(s->sin_port);
                inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);
            }

        }

    }

    m_IPSet.SetIPPack(ipstr,port);
}

int SocketBase::GetSocketDescriptor()
{
    return m_socketDescriptor;
}

void SocketBase::GetAddress(struct sockaddr_in *sin)
{
    memcpy(sin,&m_socketAddress,sizeof(struct sockaddr_in));
}

void SocketBase::SetIp(struct sockaddr_in addr)
{
    memcpy(&m_socketAddress.sin_addr,&addr.sin_addr,sizeof(struct in_addr));
}

void SocketBase::SetAddress(struct sockaddr_in addr)
{
    memcpy(&m_socketAddress,&addr,sizeof(struct sockaddr_in));
}

int SocketBase::IpEqual(struct sockaddr_in addr)
{
    fprintf(stdout,"IpEquiv: %s <=> ", inet_ntoa(m_socketAddress.sin_addr));
    fprintf(stdout,"%s\n", inet_ntoa(addr.sin_addr));
    return (memcmp(&m_socketAddress.sin_addr,&addr.sin_addr,sizeof(struct in_addr)) == 0) ? 1 : 0;
}

int SocketBase::SetSocketFlags(int sock,int newFlag)
{
    int flags;
    flags = fcntl (sock,F_GETFL, 0);
    if (flags == -1)
    {
        perror ("fcntl");
        return -1;
    }

    flags |= newFlag;//O_NONBLOCK;

    if (fcntl (sock,F_SETFL, flags) < 0)
    {
        perror ("fcntl");
        return -1;
    }
    return 1;
}

int SocketBase::ResolveHostName(const char* hostname, struct in_addr* addr)
{
    struct addrinfo *resultAddrinfo;

    int result = getaddrinfo (hostname, NULL, NULL, &resultAddrinfo);

    if (0 == result)
    {
        memcpy(addr, &((struct sockaddr_in *) resultAddrinfo->ai_addr)->sin_addr, sizeof(struct in_addr));
        freeaddrinfo(resultAddrinfo);
    }

    return result;
}

long SocketBase::BytesAvailable()
{
    long nbytesAvailable = 0;
    if(ioctl(m_socketDescriptor,FIONREAD,&nbytesAvailable) < 0)
        nbytesAvailable = -1;

//    printf("Bytes Available %ld\n", nbytesAvailable );
    return nbytesAvailable;
}

bool SocketBase::WaitForReadEvent(int timeoutInSec)
{
    fd_set sdset;
    struct timeval tv;

    tv.tv_sec = timeoutInSec;
    tv.tv_usec = 0;
    FD_ZERO(&sdset);
    FD_SET(m_socketDescriptor, &sdset);
    if (select(m_socketDescriptor+1, &sdset, NULL, NULL, &tv) > 0)
    {
        return true;
    }
    return false;
}
