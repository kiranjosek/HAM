#ifndef SUBSCRIBERSERVER_H
#define SUBSCRIBERSERVER_H

#include "SocketInfo.h"
#include "DataMultiplexer.h"
#include "SocketWatcher.h"
//#include "SocketClass.h"

//#define pEDGETRIGGERED 3


class SubscriberServer : public SocketWatcher
{
public:
    SubscriberServer(int port);
    SubscriberServer(char* ipAddr,int port);
    ~SubscriberServer();

    virtual void EventErrorHandler(struct epoll_event &event);
    virtual void AcceptNewClientConnection(struct epoll_event &event);
    virtual void ProcessClientEvent(struct epoll_event &event);

};

#endif // SUBSCRIBERSERVER_H
