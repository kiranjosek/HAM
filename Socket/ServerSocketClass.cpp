#include "ServerSocketClass.h"

ServerSocketClass::ServerSocketClass()
{
}

int ServerSocketClass::CreateServerSocket(int port)
{
    m_socketType = SOCKET_CLIENT;
    m_IPSet.SetIPPack(NULL,port);

    int status,sockopton;

    if ((m_socketDescriptor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        //SetErrorString("socket() failed");
        m_socketDescriptor = -1;
        return -1;
    }

    sockopton = 1;

    status = setsockopt(m_socketDescriptor, SOL_SOCKET, SO_REUSEADDR, (char*) &sockopton, sizeof(sockopton));

    if(status < 0)
    {
        perror("setsockopt(SO_REUSEADDR=1)");
        exit(0);
    }

    memset(&m_socketAddress, 0, sizeof(m_socketAddress));
    m_socketAddress.sin_family = AF_INET;
    m_socketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    m_socketAddress.sin_port = htons(port);

    if (bind(m_socketDescriptor, (struct sockaddr *) &m_socketAddress, sizeof(m_socketAddress)) < 0)
    {
        //SetErrorString("bind() failed");
        m_socketDescriptor = -1;
        return -1;
    }

    if (listen(m_socketDescriptor, MAXPENDING) < 0)
    {
        //SetErrorString("listen() failed");
        m_socketDescriptor = -1;
        return -1;
    }

    printf("Server Listening at Port %d\n",port);

    return m_socketDescriptor;
}
