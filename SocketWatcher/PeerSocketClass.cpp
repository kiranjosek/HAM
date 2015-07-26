#include "PeerSocketClass.h"

//pthread_mutex_t m_peerlock = PTHREAD_MUTEX_INITIALIZER;

PeerSocketClass::PeerSocketClass()
{
    //    CreateEpollSocket(sockFd,1);
    CreatePeerEpollSocket(DEFAULT_SERVER_EVENTS|EPOLLET,64);
    watchEvent = &SocketWatcher::StartPeerWatcher;
    pthread_mutex_init(&m_peerlock,NULL);
    printf("Peer Watcher\n");
}

PeerSocketClass::~PeerSocketClass()
{
    pthread_mutex_destroy(&m_peerlock);
}

void PeerSocketClass::AddSocketToPeerWatch(char* ipAddr,int port)
{
    pthread_mutex_lock(&m_peerlock);
    int sockFd = CreateClientSocket(ipAddr,port);
    IPPack* pif = new IPPack(ipAddr,port);
    pif->m_socketDescriptor = sockFd;
    m_socketIdMap[sockFd] = pif;
    //    pif.show();
    printf("New Socket Descriptor: %d\n",sockFd);
    void* memPtr =  AddSocketForWatch(sockFd,new SocketInfo(sockFd,64));
    if(memPtr)
        m_socketIdMemoryMap[sockFd] = memPtr;
    pthread_mutex_unlock(&m_peerlock);
}

void PeerSocketClass::AddSocketToPeerWatch(IPPack* pif)
{
    printf("PeerSocketClass::AddSocketToPeerWatch(IPPack,%d);\n",pif->m_socketDescriptor);

    pthread_mutex_lock(&m_peerlock);
    m_socketIdMap[pif->m_socketDescriptor] = pif;
    printf("New Socket Descriptor: %d\n",pif->m_socketDescriptor);
    void* memPtr  = AddSocketForWatch(pif->m_socketDescriptor,new SocketInfo(pif->m_socketDescriptor,64));
    if(memPtr)
        m_socketIdMemoryMap[pif->m_socketDescriptor] = memPtr;
    pthread_mutex_unlock(&m_peerlock);
}

IPPack* PeerSocketClass::RemoveSocketFromPeerWatch(int sockfd)
{
    printf("PeerSocketClass::RemoveSocketFromPeerWatch(%d);\n",sockfd);

    map<int,IPPack*>::iterator iterFind  = m_socketIdMap.find(sockfd);
    map<int,void*>::iterator iterFindMem = m_socketIdMemoryMap.find(sockfd);

    if(iterFind != m_socketIdMap.end())
    {
        pthread_mutex_lock(&m_peerlock);
        IPPack* &pif = iterFind->second;
        m_socketIdMap.erase(iterFind);
        if(iterFindMem != m_socketIdMemoryMap.end())
        {
            SocketInfo* memPtr = (SocketInfo*)iterFindMem->second;
            delete [] memPtr;
            memPtr = NULL;
        }
        pthread_mutex_unlock(&m_peerlock);

        return pif;
    }

    return NULL;
}

void PeerSocketClass::EventErrorHandler(struct epoll_event &event)
{
    printf("PeerSocketClass::EventErrorHandler();\n");
    SocketInfo* dh = (SocketInfo*)event.data.ptr;
    if(dh)
    {
        close (dh->m_socketDescriptor);
        IPPack* pif = RemoveSocketFromPeerWatch(dh->m_socketDescriptor);
        delete dh;
        dh = NULL;
        if(pif)
            delete pif;
        pif = NULL;

    }

}
