#ifndef SOCKETINFO_H
#define SOCKETINFO_H
#include "BufferedReader.h"
#include "BufferedWriter.h"

class SocketInfo : public BufferedReader
{
public:
    SocketInfo(int fd,long bufferSize);
    ~SocketInfo();

    int m_socketDescriptor;
    void* m_dataPtr;
    //BufferedReader* m_bufferedReader;
    //BufferedWriter* m_bufferedWriter;
};

#endif // SOCKETINFO_H
