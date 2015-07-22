#ifndef BUFFEREDREADER_H
#define BUFFEREDREADER_H
#include "DataHolder.h"
#include "CallBackClass.h"

#include "DataMultiplexer.h"
#include <errno.h>
#include <stdio.h>
//DataMultiplexer MUXER;

class BufferedReader: public DataHolder
{
public:

    BufferedReader(long bufferSize);
    void ReadLength(int sock,int &status);
    void ReadData(int sock,int &status);
    void ReadFromSocket(int sock,int &status);

protected:
    virtual void ProcessData();
private:
        void (BufferedReader::*ReadFromDescriptor)(int,int&);

};

#endif // BUFFEREDREADER_H
