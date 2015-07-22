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
    void SetPeerNode(map<string,IPPack*> &peerNodes,string myName);
    void ShowPeerLoop();
    PeerNode*& GetConnectedNode();
    PeerNode*& GetThisNode();

    void AddPeerToRightOfNode(string node_name, PeerNode* newNode);

/*
    virtual void EventErrorHandler(struct epoll_event &event);
    virtual void AcceptNewClientConnection(struct epoll_event &event);
    virtual void ProcessClientEvent(struct epoll_event &event);
*/
};

#endif // PEERCOMMUNICATOR_H
