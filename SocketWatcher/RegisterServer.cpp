#include "RegisterServer.h"

RegisterServer::RegisterServer(int port)
{
    int sockFd= CreateServerSocket(port);
    CreateEpollSocket(sockFd);
    watchEvent = &SocketWatcher::StartServerWatcher;
    printf("Register Server\n");
}

RegisterServer::RegisterServer(char* ipAddr,int port)
{
    int sockFd = CreateClientSocket(ipAddr,port);
//    CreateEpollSocket(sockFd,1);
    CreateEpollSocket(sockFd,DEFAULT_SERVER_EVENTS|EPOLLET,new SocketInfo(sockFd,64));
    watchEvent = &SocketWatcher::StartClientWatcher;
    //MUXER.AddSubscriberSocket(sockFd);
    printf("Register Client\n");
}

void RegisterServer::EventErrorHandler(struct epoll_event &event)
{
    printf("RegisterServer::EventErrorHandler();\n");
    SocketInfo* dh = (SocketInfo*)event.data.ptr;
    //MUXER.RemoveSubscriberSocket(dh->m_socketDescriptor);
    close (dh->m_socketDescriptor);
    delete dh;
}

void RegisterServer::AcceptNewClientConnection(struct epoll_event &event)
{
    printf("RegisterServer()::AcceptNewClientConnection()\n");

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

    //MUXER.AddSubscriberSocket(infd);

}

void RegisterServer::ProcessClientEvent(struct epoll_event &event)
{

    printf("RegisterServer::ProcessClientEvent();\n");
    int done = 0;

    SocketInfo* dh = (SocketInfo*)event.data.ptr;
#ifdef EDGETRIGGERED
    while(1)
    {
#endif

        dh->ReadFromSocket(dh->m_socketDescriptor,done);
        if(done == 1) // socket read Error
        {
            EventErrorHandler(event);
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
