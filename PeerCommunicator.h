#ifndef PEERCOMMUNICATOR_H
#define PEERCOMMUNICATOR_H

#include "PeerNode.h"
#include <map>

class PeerCommunicator //:public SocketWatcher/*, public SocketClass*/
{
    PeerNode* m_peerLoopStart;
    PeerNode* m_connectedPeers;
    PeerNode* m_thisNode;
//    PeerNode* m_thisNode;

public:

    PeerCommunicator();
    void SetPeerNode(map<string,IPPack*> &peerNodes,int myPosition);
    void ShowPeerLoop();
    PeerNode*& getConnectedNode();
    PeerNode*& getThisNode();
/*
    virtual void EventErrorHandler(struct epoll_event &event);
    virtual void AcceptNewClientConnection(struct epoll_event &event);
    virtual void ProcessClientEvent(struct epoll_event &event);
*/
};

#endif // PEERCOMMUNICATOR_H
