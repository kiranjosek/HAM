#ifndef PEERSOCKETCLASS_H
#define PEERSOCKETCLASS_H

#include <map>

using namespace std;

#include "SocketInfo.h"
#include "DataMultiplexer.h"
#include "SocketWatcher.h"
#include "SocketClass.h"
#include "IPPack.h"

void *reconnectClient(void *arg);

class PeerSocketClass : public SocketWatcher/*, public SocketClass*/
{
    pthread_mutex_t m_peerlock ;
    map<int,IPPack*> m_socketIdMap;
    map<int,void*> m_socketIdMemoryMap;

public:

    PeerSocketClass();
    ~PeerSocketClass();

    void AddSocketToPeerWatch(char* ipAddr,int port);
    void AddSocketToPeerWatch(IPPack* pif);
    IPPack* RemoveSocketFromPeerWatch(int sockfd);
    virtual void EventErrorHandler(struct epoll_event &event);
    //    virtual void AcceptNewClientConnection(struct epoll_event &event);
    //    virtual void ProcessClientEvent(struct epoll_event &event);
};


#endif // PeerSocketClass_H
