#include "HAMCore.h"

extern  PeerWatcher PEERWATCHER;

void *peerMonitor(void*)
{
    pthread_t tid1;

    //    PEERWATCHER.getConnectedNode()->m_IPSet->show();

    int err1 = pthread_create(&tid1, NULL, reconnectClient, PEERWATCHER.getConnectedNode()->m_IPSet);
    if(err1 < 0)
    {
        cerr << "Thread CreationFailed in connecting to Peer\n";
    }

    PEERWATCHER.StartWatcher();
    return NULL;
}

void HAMCore::processRequest()
{

}

HAMCore::HAMCore():RegisterServer(PEERWATCHER.getThisNode()->m_IPSet->m_port)
{

}

void HAMCore::startPeerMonitor()
{
    pthread_t tid;

    int err = pthread_create(&tid, NULL, peerMonitor, NULL);

    if(err < 0)
    {
        cerr << "Thread Failed in Peer Monitoring\n";
    }

}

void HAMCore::HAMStart()
{
    this->startPeerMonitor();
    this->StartWatcher();
}

void HAMCore::ProcessClientEvent(struct epoll_event &event)
{

    int done = 0; // success

    SocketInfo* dh = (SocketInfo*)event.data.ptr;
#ifdef EDGETRIGGERED
    while(1)
    {
#endif
        dh->ReadFromSocket(dh->m_socketDescriptor,done);// call back........ needed
        if(done == 0)
        {
            printf("virtual ProcessData() : %u %s",*dh->m_dataLength, ((char*)dh->m_dataBuffer)+ sizeof(unsigned int));
            dh->ResetPosition();
        }
        if(done == 1) // socket read Error
        {
            EventErrorHandler(event);
            /*
            printf("Socket Closing()\n");
            SocketInfo* dh = (SocketInfo*)event.data.ptr;
            close (dh->m_socketDescriptor);
            delete dh;
            */
            return;

        }
#ifdef EDGETRIGGERED

        else if(done == 2) //EAGAIN
        {
            return;
        }

    }
#endif
}
