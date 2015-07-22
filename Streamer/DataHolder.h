#ifndef DATAHOLDER_H
#define DATAHOLDER_H
//#include "MemoryPool.h"
#include <sys/epoll.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
class DataStream : public MemoryPool
{
public:
    char* m_buffer;
};
*/

class DataHolder
{
public:

    unsigned int* m_dataLength;
    char* m_dataBuffer;
    char* m_position;
    unsigned int m_bufferSize;      //  buffer size + size of (unsigned int)

    DataHolder(int size);
    void ResetPosition();
    void CheckForBufferSize();
    char* GetBuffer();
    unsigned int GetBufferSize();
    ~DataHolder();

};


#endif // DATAHOLDER_H
