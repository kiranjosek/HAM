#include "SocketWatcher.h"
//#include "SocketInfo.h"

#define EDGETRIGGERED 1

#ifndef EPOLLRDHUP
#define EPOLLRDHUP 0x2000
#endif

SocketWatcher::SocketWatcher()
{
    m_epollWaitTimer = -1;
    m_events = NULL;
}

SocketWatcher::~SocketWatcher()
{
    if(m_events)
        free(m_events);
}

void SocketWatcher::setWatcherWaitTimer(long timeInMilliSec)
{
    m_epollWaitTimer = timeInMilliSec;
}

void SocketWatcher::CreateEpollSocket(int listeningSocket, int maximumEvent, uint32_t eventsToHandle)
{
    if(listeningSocket == -1)
    {
        printf("CreateEpollSocket(): Invalid Socket\n");
        return;
    }

    m_socketDescriptor = listeningSocket; // Copying to Member
    m_eventsToHandle = eventsToHandle;
    m_maximumEventCount = maximumEvent;
    AddDescriptor();
}

void SocketWatcher::CreateEpollSocket(int clientSocketfd,uint32_t eventsToHandle,void* buffer)
{
    m_socketDescriptor = clientSocketfd; // Copying to Member
    m_maximumEventCount = 1;
    m_eventsToHandle = eventsToHandle;
    epoll_data_t eventData;
    eventData.ptr = buffer;
    AddDescriptor(&eventData);
}

void SocketWatcher::CreatePeerEpollSocket(uint32_t eventsToHandle,int maxEvent)
{
    printf("Peer Socket.....................\n");
    m_maximumEventCount = 0;
    m_eventsToHandle = eventsToHandle;
    m_epollDescriptor = epoll_create(maxEvent);
}

void SocketWatcher::AddSocketForWatch(int infd,void* buff)
{
    if(SetSocketFlags(infd,O_NONBLOCK) < 0)
    {
        perror ("AddSocketForWatch Flag Error:");
        return;// exit()
    }

    ++m_maximumEventCount;

    struct epoll_event event;
    event.data.ptr = buff;

#ifdef EDGETRIGGERED
    event.events = EPOLLIN | EPOLLET | EPOLLERR | EPOLLRDHUP | EPOLLHUP;
#else
    event.events = EPOLLIN | EPOLLERR | EPOLLRDHUP | EPOLLHUP;
#endif
    if(epoll_ctl(m_epollDescriptor,EPOLL_CTL_ADD,infd,&event))
    {
        perror ("epoll_ctl");
        return; // exit()
    }


    if(m_events == NULL)
        m_events = (struct epoll_event*)calloc(1024,sizeof(epoll_event)); // neeed change


}

void SocketWatcher::AddDescriptor(void* eventData)
{

    m_epollDescriptor = epoll_create(m_maximumEventCount);

    if(m_epollDescriptor < 0)
    {
        perror("Epoll Create Error\n");
        m_socketStatus = errno;
        return;
    }

    if(SetSocketFlags(m_socketDescriptor,O_NONBLOCK) < 0)
    {
        perror("Set Socket Flag\n");
        m_socketStatus = errno;
        return;
    }

    if(m_maximumEventCount == 1)
    {
        //m_event.data.fd = m_socketDescriptor;
        memcpy(&m_event.data,eventData,sizeof(m_event.data));// = new SocketInfo(m_socketDescriptor,64);
    }
    else
    {
        m_event.data.fd = m_socketDescriptor;
    }

    m_event.events = m_eventsToHandle;//| EPOLLET;

    if(epoll_ctl(m_epollDescriptor,EPOLL_CTL_ADD,m_socketDescriptor,&m_event) < 0)
    {
        perror ("epoll_ctl:");
        return;
    }

    m_events = (struct epoll_event*)calloc(m_maximumEventCount,sizeof(epoll_event));

    printf("AddDescriptor Done\n");

}

void SocketWatcher::StartWatcher()
{
    (this->*watchEvent)();
}

void SocketWatcher::StartServerWatcher()
{
    printf("startServerWatcher\n");
    int numberOfPollEvent,i;

    while(1)
    {
        //printf("Event");
        fflush(stdout);

        numberOfPollEvent = epoll_wait(m_epollDescriptor,m_events,m_maximumEventCount,m_epollWaitTimer);

        //printf(" Occured: Count %d \n",numberOfPollEvent);

        for (i=0; i < numberOfPollEvent; i++) // loop each events
        {
            //printf("for [%d] \n",i);
            if (( (m_events[i].events & EPOLLERR) || (m_events[i].events & EPOLLRDHUP)
                ||  (m_events[i].events & EPOLLHUP) ))// && (!(m_events[i].events & EPOLLIN)))
                {
                EventErrorHandler(m_events[i]);
            }
            else if(m_events[i].events & EPOLLIN)
            {
                if (m_socketDescriptor == m_events[i].data.fd)
                {
                    AcceptNewClientConnection(m_event);
                    //continue;
                }
                else // Event On Client Socket
                {
                    ProcessClientEvent(m_events[i]);
                    //        printf("Returned\n");
                }
                //      printf("ELSe\n");
            }

            //    printf("Completed");
            fflush(stdout);

        }
        //  printf("Next While...");
        fflush(stdout);

    }

    free(m_events);
}

void SocketWatcher::StartClientWatcher()
{
    printf("startClientWatcher\n");
    int numberOfPollEvent,i=0;

    while(1)
    {
        numberOfPollEvent = epoll_wait(m_epollDescriptor,m_events,m_maximumEventCount,m_epollWaitTimer);

        //printf(" Occured: Count %d \n",numberOfPollEvent);

        //for (i=0;i<numberOfPollEvent;i++) // loop each events
        if(numberOfPollEvent > 0)
        {
            //printf("for [%d] \n",i);
            if (( (m_events[i].events & EPOLLERR) || (m_events[i].events & EPOLLRDHUP)
                ||  (m_events[i].events & EPOLLHUP) ))// && (!(m_events[i].events & EPOLLIN)))
                {
                EventErrorHandler(m_events[i]);
            }
            else if(m_events[i].events & EPOLLIN)
            {
                ProcessClientEvent(m_events[i]);
            }

        }
        fflush(stdout);

    }

    free(m_events);
}

void SocketWatcher::StartPeerWatcher()
{
//    printf("StartPeerWatcher\n");
    int numberOfPollEvent,i;

    while(1)
    {
        //printf("Event");
        fflush(stdout);

        numberOfPollEvent = epoll_wait(m_epollDescriptor,m_events,m_maximumEventCount,m_epollWaitTimer);

        //printf(" Occured: Count %d \n",numberOfPollEvent);

        for (i=0; i < numberOfPollEvent; i++) // loop each events
        {
            //printf("for [%d] \n",i);
            if (( (m_events[i].events & EPOLLERR) || (m_events[i].events & EPOLLRDHUP)
                ||  (m_events[i].events & EPOLLHUP) ))// && (!(m_events[i].events & EPOLLIN)))
                {
                EventErrorHandler(m_events[i]);
            }
            else if(m_events[i].events & EPOLLIN)
            {
                ProcessClientEvent(m_events[i]);
            }

            //    printf("Completed");
            fflush(stdout);

        }
        //  printf("Next While...");
        fflush(stdout);

    }

    free(m_events);
}

void SocketWatcher::EventErrorHandler(struct epoll_event &event)
{
#if 0
    printf("Socket Watcher: EventErrorHandler()\n");

    SocketInfo* dh = (SocketInfo*)event.data.ptr;
    close (dh->m_socketDescriptor);
    delete dh;
#endif
}

void SocketWatcher::AcceptNewClientConnection(struct epoll_event &event)
{
    printf("Socket Watcher: AcceptNewClientConnection()\n");
#if 0
    //while(1)
    {
        struct sockaddr in_addr;
        socklen_t in_len;
        int infd;
        //char hbuf[MAXBUFSIZE], sbuf[MAXBUFSIZE];

        in_len = sizeof in_addr;
        infd = accept(m_socketDescriptor,&in_addr,&in_len);
        if (infd == -1) //error or Exception
        {
            /*
//            if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
//            {
//                //  We have processed all incoming connections.
//                //break;
//            }
//            else
//            {
//                perror ("accept"); // error in accepting connection
//                //break;
//            }
            */
            return;
        }
        /*
//        if(getnameinfo(&in_addr,in_len,
//                       hbuf,sizeof hbuf,
//                       sbuf,sizeof sbuf,
//                       NI_NUMERICHOST | NI_NUMERICSERV) == 0)
//        {
//            printf("Accepted connection on descriptor %d "
//                   "(host=%s, port=%s)\n", infd, hbuf, sbuf);
//            fflush(stdout);
//        }
*/
        /* Make the incoming socket non-blocking and add it to the list of fds to monitor. */

        if(SetSocketFlags(infd,O_NONBLOCK) < 0)
        {
            perror ("Flag Error:");
            return;// exit()
        }

        event.data.ptr = new SocketInfo(infd,64);
#ifdef EDGETRIGGERED
        event.events = EPOLLIN | EPOLLET | EPOLLERR | EPOLLRDHUP | EPOLLHUP;
#else
        event.events = EPOLLIN | EPOLLERR | EPOLLRDHUP | EPOLLHUP;
#endif
        if(epoll_ctl(m_epollDescriptor,EPOLL_CTL_ADD,infd,&event))
        {
            perror ("epoll_ctl");
            return; // exit()
        }
        //MUXER.AddSubscriberSocket(infd);

    }

#endif
}

void SocketWatcher::ProcessClientEvent(struct epoll_event &event)
{

    printf("Socket Watcher: ProcessClientEvent();");

#if 0


    int done = 0; // success

    SocketInfo* dh = (SocketInfo*)event.data.ptr;
#ifdef EDGETRIGGERED
    while(1)
    {
#endif
        //MUXER.RemoveSubscriberSocket(dh->m_socketDescriptor);

        dh->m_bufferedReader->ReadFromSocket(dh->m_socketDescriptor,done);
        if(done == 1) // socket read Error
        {

            SocketInfo* dh = (SocketInfo*)event.data.ptr;
            //      printf("Closed connection on descriptor %d\n",dh->m_socketDescriptor);
            close (dh->m_socketDescriptor);
            delete dh;
            return;

        }
#ifdef EDGETRIGGERED

        else if(done == 2) //EAGAIN
        {
            //    printf("EAGAIN\n");
            return;
        }

    }
#endif
    //printf("\n\t\t\tReturning\n");
#endif
}

