#include "SocketInfo.h"

SocketInfo::SocketInfo(int fd,long bufferSize):  BufferedReader(bufferSize)
{
    m_socketDescriptor = fd;
    m_dataPtr = NULL;
//    m_bufferedReader = new BufferedReader(bufferSize);
//    m_bufferedWriter = new BufferedWriter();
}

SocketInfo::~SocketInfo()
{
    if(m_dataPtr)
        delete m_dataPtr;
    /*
    if(m_bufferedReader)
        delete m_bufferedReader;
        */
}

/*
int SocketInfo::SocketDescriptor()
{
    return m_socketDescriptor;
}
*/
