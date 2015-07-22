#include "DataHolder.h"
#include <iostream>
#include <string.h>
using namespace std;

DataHolder::DataHolder(int size)
{
    m_bufferSize = size+sizeof(unsigned int);
    m_dataBuffer = new char[m_bufferSize];
    ResetPosition();
}

DataHolder::~DataHolder()
{
    delete [] m_dataBuffer;
}

void DataHolder::ResetPosition()
{
    m_position = (char*)m_dataBuffer;
    m_dataLength = (unsigned int*)m_dataBuffer;

}

char* DataHolder::GetBuffer()
{
    return (char*)m_dataBuffer;
}

unsigned int DataHolder::GetBufferSize()
{
    return m_bufferSize;
}


void DataHolder::CheckForBufferSize()
{
 //   cerr << (*m_dataLength)+sizeof(unsigned int) << "^^^" << m_bufferSize <<endl;

    if((*m_dataLength)+sizeof(unsigned int) > m_bufferSize)
    {
        unsigned int lengthOfData = *m_dataLength;
        m_bufferSize = lengthOfData+sizeof(unsigned int);
        delete[] m_dataBuffer;
        m_dataBuffer = new char[m_bufferSize];
        ResetPosition();

        *m_dataLength = lengthOfData;
        m_position += sizeof(unsigned int);

    }

   // cerr << "Done\n";
}
