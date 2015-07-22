#include "HAMCore.h"

extern  PeerWatcher PEERWATCHER;

void *peerMonitor(void*)
{
    pthread_t tid1;

    //    PEERWATCHER.getConnectedNode()->m_IPSet->show();

    int err1 = pthread_create(&tid1, NULL, reconnectClient, PEERWATCHER.GetConnectedNode()->m_IPSet);
    if(err1 < 0)
    {
        cerr << "Thread CreationFailed in connecting to Peer\n";
    }

    PEERWATCHER.setWatcherWaitTimer(10000);
    PEERWATCHER.StartWatcher();
    return NULL;
}

void HAMCore::processRequest()
{

}

HAMCore::HAMCore():RegisterServer(PEERWATCHER.GetThisNode()->m_IPSet->m_port)
{

}

void HAMCore::startPeerMonitor()
{
//    while(1)
    {
        pthread_t tid;

        int err = pthread_create(&tid, NULL, peerMonitor, NULL);

        if(err < 0)
        {
            cerr << "Thread Failed in Peer Monitoring\n";
        }
        sleep(10);
        cerr << "Peer Monitor Restarting\n";
    }

}

void HAMCore::HAMStart()
{
    this->startPeerMonitor();

    sleep(15);
    int scd = PEERWATCHER.GetConnectedNode()->m_IPSet->m_socketDescriptor;
    PEERWATCHER.AddPeerToRightOfNode(PEERWATCHER.GetConnectedNode()->GetNodeName(),new PeerNode("NewNode", new IPPack("0.0.0.0",9996)));

    PEERWATCHER.GetConnectedNode() = PEERWATCHER.GetConnectedNode()->GetLeftPeer();

    PEERWATCHER.ShowPeerLoop();



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
