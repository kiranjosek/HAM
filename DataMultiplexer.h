#ifndef DATAMULTIPLEXER_H
#define DATAMULTIPLEXER_H
#include <pthread.h>
#include <vector>

using namespace std;

#include "BufferedWriter.h"


class DataMultiplexer
{
    vector<int> m_clientList;

    BufferedWriter m_bufferWriter;

public:
    DataMultiplexer();
    void RemoveSubscriberSocket(int sock);
    void AddSubscriberSocket(int sock);

    void MultiplexData(char* buff);
};

//extern DataMultiplexer MUXER;


#endif // DATAMULTIPLEXER_H
