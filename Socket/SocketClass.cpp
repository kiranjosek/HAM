#include "SocketClass.h"

SocketClass::SocketClass()
{
}

int SocketClass::CreateSocket(int port,char* ip)
{
    if(ip)
        return CreateClientSocket(ip,port);

    return CreateServerSocket(port);
}

int SocketClass::CreateClientSocket(char* ip,int port)
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

int SocketClass::CreateClientSocket(char* server, int port, int timeout)
        // IPPack is not set. need to completed some code that are in CreateClientSocket(IP,Port)
{
    if (timeout == 0)
        return CreateClientSocket(server, port);
    m_socketType = SOCKET_CLIENT;

    printf("\nEstablishing connection to server with Time Out of %d Sec",timeout);


    memset (&m_socketAddress, 0, sizeof(m_socketAddress));
    m_socketAddress.sin_family = AF_INET;
    m_socketAddress.sin_port = htons(port);
    if (ResolveHostName(server, &(m_socketAddress.sin_addr)) != 0 )
    {
        inet_pton(PF_INET, server, &(m_socketAddress.sin_addr));
    }

    m_IPSet.SetIPPack(server,port);

    long arg;
    fd_set sd;
    struct timeval tv;
    socklen_t len;
    int valopt /* ,result = -1*/;

    m_socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    // Set socket to non-blocking
    arg = fcntl(m_socketDescriptor, F_GETFL, NULL);
    arg |= O_NONBLOCK;
    fcntl(m_socketDescriptor, F_SETFL, arg);

    // Connect with time limit
    if ((/*result = */::connect(m_socketDescriptor, (struct sockaddr *)&m_socketAddress, sizeof(m_socketAddress))) < 0)
    {
        if (errno == EINPROGRESS)
        {
            tv.tv_sec = timeout;
            tv.tv_usec = 0;
            FD_ZERO(&sd);
            FD_SET(m_socketDescriptor, &sd);
            if (select(m_socketDescriptor+1, NULL, &sd, NULL, &tv) > 0)
            {
                len = sizeof(int);
                getsockopt(m_socketDescriptor, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &len);
                if (valopt)
                {
                    close(m_socketDescriptor);
                    m_socketDescriptor = -1;
                    fprintf(stderr, "\nconnect() error %d - %s\n", valopt, strerror(valopt));
                    return -1;
                }

                // connection established
            }
            else
            {
                close(m_socketDescriptor);
                m_socketDescriptor = -1;
                fprintf(stderr, "\nconnect() timed out\n");
                return -1;
            }
        }
        else
        {
            close(m_socketDescriptor);
            m_socketDescriptor = -1;
            fprintf(stderr, "\nconnect() error %d - %s\n", errno, strerror(errno));
            return -1;
        }
    }
    else
    {
        close(m_socketDescriptor);
        m_socketDescriptor = -1;
        fprintf(stderr, "connect() failed %d - %s\n", errno, strerror(errno));
        return -1;
    }

    // Return socket to blocking mode
    arg = fcntl(m_socketDescriptor, F_GETFL, NULL);
    arg &= (~O_NONBLOCK);
    fcntl(m_socketDescriptor, F_SETFL, arg);

    return m_socketDescriptor;
}

int SocketClass::CreateServerSocket(int port)
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
