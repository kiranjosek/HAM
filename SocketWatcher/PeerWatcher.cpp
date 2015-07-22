#include "PeerWatcher.h"

PeerWatcher PEERWATCHER;

void *reconnectClient(void *arg)
{
    IPPack* pifPtr = (IPPack*)arg;
    //    pifPtr->show();
    sleep(4);
    PEERWATCHER.getConnectedNode()->m_IPSet = pifPtr;

    SocketClass sockObj;
    int sockFd = -1;

    sockFd = sockObj.CreateClientSocket(pifPtr->m_ip,pifPtr->m_port);
    while(sockFd < 0)
    {
        PEERWATCHER.getConnectedNode() =     PEERWATCHER.getConnectedNode()->GetRightPeer();
        sleep(4);
        PEERWATCHER.getConnectedNode()->m_IPSet->show();
        sockFd = sockObj.CreateClientSocket(PEERWATCHER.getConnectedNode()->m_IPSet->m_ip,PEERWATCHER.getConnectedNode()->m_IPSet->m_port,10);

        printf("Reconneting in 4 Sec...");
    }
    //    pthread_mutex_lock(&peerlock);
    //    PEERWATCHER.m_socketIdMap[sockFd] = pifPtr;
    //    PEERWATCHER.AddSocketForWatch(sockFd,new SocketInfo(sockFd,64));
    //    pthread_mutex_unlock(&peerlock);

    PEERWATCHER.AddSocketToPeerWatch(PEERWATCHER.getConnectedNode()->m_IPSet,sockFd);
/*
    SocketClass sc;
    sc.SetSocketDescriptor(sockFd);
    */
    //    sc.BytesAvailable();
    return 0;
}


PeerWatcher::PeerWatcher()
{
}

PeerWatcher::~PeerWatcher()
{
}

void PeerWatcher::EventErrorHandler(struct epoll_event &event)
{
    printf("PeerWatcher::EventErrorHandler();\n");
    SocketInfo* dh = (SocketInfo*)event.data.ptr;
    close (dh->m_socketDescriptor);
    IPPack* pif = RemoveSocketFromPeerWatch(dh->m_socketDescriptor);
    delete dh;


    if(pif)
    {
        pthread_t tid;

        int err = pthread_create(&tid, NULL, reconnectClient, pif);
        if (err != 0)
        {
            exit(err);
        }
    }
}
