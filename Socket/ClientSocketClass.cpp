#include "ClientSocketClass.h"

ClientSocketClass::ClientSocketClass()
{
}

int ClientSocketClass::CreateClientSocket(char* ip,int port)
{
    m_socketType = SOCKET_CLIENT;
    m_IPSet.SetIPPack(ip,port);
    memset(&m_socketAddress,0x00, sizeof(struct sockaddr_in));
    m_socketAddress.sin_family = AF_INET;
    m_socketAddress.sin_port = htons(port);
    m_socketAddress.sin_addr.s_addr = inet_addr(ip);
    m_socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(m_socketDescriptor, (struct sockaddr *) &m_socketAddress, sizeof(m_socketAddress)) < 0 )
    {
        close(m_socketDescriptor);
        m_socketDescriptor = -1;
        printf("Not Able To connect to %s:%d\n",ip,port);
        return -1;
    }

    printf("Connected to %s:%d\n",ip,port);

    return m_socketDescriptor;
}
