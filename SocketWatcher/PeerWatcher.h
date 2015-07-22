#ifndef PEERWATCHER_H
#define PEERWATCHER_H
#include "PeerSocketClass.h"
#include "PeerCommunicator.h"

class PeerWatcher : public PeerSocketClass, public PeerCommunicator
{
public:
    PeerWatcher();
    ~PeerWatcher();

    virtual void EventErrorHandler(struct epoll_event &event);

};

#endif // PEERWATCHER_H
