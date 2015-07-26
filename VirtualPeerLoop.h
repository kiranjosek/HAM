#ifndef VIRTUALPEERLOOP_H
#define VIRTUALPEERLOOP_H

#include "PeerNode.h"
#include <map>

class VirtualPeerLoop //:public SocketWatcher/*, public SocketClass*/
{
    PeerNode* m_peerLoopStart;
    PeerNode* m_connectedPeers;
    PeerNode* m_thisNode;
//    PeerNode* m_thisNode;

public:

    VirtualPeerLoop();
    void SetPeerNode(map<string,IPPack*> &peerNodes,string myName);
    void ShowPeerLoop();
    PeerNode*& GetConnectedNode();
    PeerNode*& GetThisNode();

    string GetNodeAsBuffer();
    void SetPeerLoopFromBuffer(string &str,map<string,IPPack*> &peerNodes);

    void AddPeerToRightOfNode(string node_name, PeerNode* newNode);

/*
    virtual void EventErrorHandler(struct epoll_event &event);
    virtual void AcceptNewClientConnection(struct epoll_event &event);
    virtual void ProcessClientEvent(struct epoll_event &event);
*/
};

#endif // VIRTUALPEERLOOP_H
