#ifndef BUFFEREDWRITER_H
#define BUFFEREDWRITER_H
#include "DataHolder.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

class BufferedWriter //: public DataStream
{
    //char *m_buffer;
public:
    BufferedWriter();
    ~BufferedWriter();
    int WriteToSocket(int socketfd,char* dataStream,long dataLength);
    int WriteToSocket(int socketfd,char* dataStream);
};

#endif // BUFFEREDWRITER_H
