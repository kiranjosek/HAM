#ifndef HAMCORE_H
#define HAMCORE_H
#include "PeerWatcher.h"
#include "RegisterServer.h"

enum HAM_CMD
{
    eHAM_RESERVED,
    eHAM_INST_REQUEST,
    eHAM_ADD_NEW_NODE,
    eHAM_RING,
    eHAM_DOWN_THIS,
    eHAM_CNODE_TEST,
    eHAM_CLUSTER_NODES,
    eHAM_CONNECTIVITY_TEST,
    eHAM_NODE_INSTANCE
};


class HAMCore : public RegisterServer
{

public:
    HAMCore();
    void startPeerMonitor();
    void HAMStart();
    virtual void ProcessClientEvent(struct epoll_event &event);
    void processRequest();





};

#endif // HAMCORE_H
