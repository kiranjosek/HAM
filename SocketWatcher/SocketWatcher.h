#ifndef SocketWatcher_H
#define SocketWatcher_H

#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <string.h>
#include "SocketClass.h"

#define MAXEVENTS 1024
#define DEFAULT_SERVER_EVENTS EPOLLIN | EPOLLERR | EPOLLRDHUP | EPOLLHUP

class SocketWatcher : public SocketClass
{
protected:

//    int m_listeningSocketDescriptor;
    int m_epollDescriptor;
    int m_socketStatus;
    uint32_t m_eventsToHandle;
    int m_maximumEventCount;
    long m_epollWaitTimer;

    struct epoll_event m_event;
    struct epoll_event* m_events;

    void (SocketWatcher::*watchEvent)();


//    int SetSocketFlags(int sock,int newFlag);
    void AddDescriptor(void* eventData = NULL);

    virtual void AcceptNewClientConnection(struct epoll_event &event);
    virtual void ProcessClientEvent(struct epoll_event &event);
    virtual void EventErrorHandler(struct epoll_event &event);

public:

    SocketWatcher();
    ~SocketWatcher();
    void CreateEpollSocket(int listeningSocket =-1,int maximumEvent=MAXEVENTS,uint32_t eventsToHandle = DEFAULT_SERVER_EVENTS);
    void CreateEpollSocket(int clientSocketfd,uint32_t eventsToHandle,void* buffer);
    void CreatePeerEpollSocket(uint32_t eventsToHandle,int maxEvent);

    void AddSocketForWatch(int infd,void* buff);
    void setWatcherWaitTimer(long timeInMilliSec);

    void StartWatcher();
    void StartServerWatcher();
    void StartClientWatcher();
    void StartPeerWatcher();

};

#endif // SocketWatcher_H
