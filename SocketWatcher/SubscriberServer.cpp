#include "SubscriberServer.h"

//DataMultiplexer MUXER;

SubscriberServer::SubscriberServer(int port)
{
    int sockFd = CreateServerSocket(port);
    CreateEpollSocket(sockFd);
    watchEvent = &SocketWatcher::StartServerWatcher;
    printf("Subscriber Server\n");
}

SubscriberServer::SubscriberServer(char* ipAddr,int port)
{
    int sockFd = CreateClientSocket(ipAddr,port);
    CreateEpollSocket(sockFd,DEFAULT_SERVER_EVENTS | EPOLLET,new SocketInfo(sockFd,64));
    watchEvent = &SocketWatcher::StartClientWatcher;
    //MUXER.AddSubscriberSocket(sockFd);
    printf("Subscriber Client\n");
}

SubscriberServer::~SubscriberServer()
{

}

void SubscriberServer::EventErrorHandler(struct epoll_event &event)
{
    int pidds = getpid();
    printf("%d :Socket Closing()\n",pidds);
    SocketInfo* dh = (SocketInfo*)event.data.ptr;
    if(epoll_ctl(m_epollDescriptor,EPOLL_CTL_DEL,dh->m_socketDescriptor,&event))
    {
        perror ("epoll_ctl");
        return; // exit()
    }

    close (dh->m_socketDescriptor);
    delete dh;
}

void SubscriberServer::AcceptNewClientConnection(struct epoll_event &event)
{
    printf("SubscriberServer::AcceptNewClientConnection();");
    struct sockaddr in_addr;
    socklen_t in_len;
    int infd;

    in_len = sizeof in_addr;
    infd = accept(m_socketDescriptor,&in_addr,&in_len);
    if (infd == -1) //error or Exception

        return;

    if(SetSocketFlags(infd,O_NONBLOCK) < 0)
    {
        perror ("Flag Error:");
        return;// exit()
    }

    event.data.ptr = new SocketInfo(infd,64);
#ifdef EDGETRIGGERED
    event.events = EPOLLIN | EPOLLET | EPOLLERR | EPOLLRDHUP | EPOLLHUP;
#else
    event.events = EPOLLIN | EPOLLERR | EPOLLRDHUP | EPOLLHUP;
#endif
    if(epoll_ctl(m_epollDescriptor,EPOLL_CTL_ADD,infd,&event))
    {
        perror ("epoll_ctl");
        return; // exit()
    }

}

void SubscriberServer::ProcessClientEvent(struct epoll_event &event)
{

    int done = 0; // success

    SocketInfo* dh = (SocketInfo*)event.data.ptr;
#ifdef EDGETRIGGERED
    while(1)
    {
#endif
        dh->ReadFromSocket(dh->m_socketDescriptor,done);
        if(done == 1) // socket read Error
        {
            EventErrorHandler(event);
            /*
            printf("Socket Closing()\n");
            SocketInfo* dh = (SocketInfo*)event.data.ptr;
            close (dh->m_socketDescriptor);
            delete dh;
            */
            return;

        }
#ifdef EDGETRIGGERED

        else if(done == 2) //EAGAIN
        {
            return;
        }

    }
#endif
}
