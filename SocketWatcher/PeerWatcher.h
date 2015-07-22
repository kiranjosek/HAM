#ifndef PEERWATCHER_H
#define PEERWATCHER_H
#include "PeerSocketClass.h"
#include "VirtualPeerLoop.h"

class PeerWatcher : public PeerSocketClass, public VirtualPeerLoop
{
public:
    PeerWatcher();
    ~PeerWatcher();

    virtual void EventErrorHandler(struct epoll_event &event);

};

#endif // PEERWATCHER_H
