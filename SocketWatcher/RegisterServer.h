#ifndef REGISTERSERVER_H
#define REGISTERSERVER_H

#include "SocketInfo.h"
#include "DataMultiplexer.h"
#include "SocketWatcher.h"
#include "SocketClass.h"

class RegisterServer : public SocketWatcher/*, public SocketClass*/
{

public:
    RegisterServer(int port);
    RegisterServer(char* ipAddr,int port);

    virtual void EventErrorHandler(struct epoll_event &event);
    virtual void AcceptNewClientConnection(struct epoll_event &event);
    virtual void ProcessClientEvent(struct epoll_event &event);
};

#endif // REGISTERSERVER_H
