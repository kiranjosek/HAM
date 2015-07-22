#include "BufferedWriter.h"

BufferedWriter::BufferedWriter()
{
    //m_buffer = NULL;
}

BufferedWriter::~BufferedWriter()
{
    /*
    if(m_buffer)
        delete []m_buffer;

    m_buffer = NULL;
    */
}

int BufferedWriter::WriteToSocket(int socketfd,char* dataStream,long dataLength)
{
    int sentBytes = 0;
    int cSendByted = 0;

    do
    {
        cSendByted = ::write(socketfd,(&dataLength)+sentBytes,sizeof(unsigned int) - sentBytes);
        if(cSendByted < 0)
        {
            if(errno  != EAGAIN )
            {
                return -1;
            }
        }
        else
        {
            sentBytes += cSendByted;
        }

    }while( !(dataLength-sentBytes) );

    sentBytes = 0;
    do
    {
        cSendByted = ::write(socketfd,dataStream+sentBytes,dataLength - sentBytes);
        if(cSendByted < 0)
        {
            if(errno  != EAGAIN )
            {
                return -1;
            }
        }
        else
        {
            sentBytes += cSendByted;
        }

    }while( !(dataLength-sentBytes) );

    return 0;
}

int BufferedWriter::WriteToSocket(int socketfd,char* dataStream)
{
    //    return WriteToSocket(socketfd,dataStream+sizeof(unsigned int),*((unsigned int *)dataStream) );

    int sentBytes = 0;
    int cSendByted = 0;

    unsigned int dataLength = *((unsigned int *)dataStream) + sizeof(unsigned int);
    //printf("Size: %d",dataLength);

    //if(dataLength==0)
    //    return 0;
    do
    {
        cSendByted = ::write(socketfd,dataStream+sentBytes,dataLength - sentBytes);
        if(cSendByted < 0)
        {
            if(errno  != EAGAIN )
            {
               perror("ERROR");
               printf("ERROROOROOR\n");
                return -1;
            }
        }
        else
        {
            sentBytes += cSendByted;
        }

        //printf("SENDING....%d\n",cSendByted);
    }while((dataLength-sentBytes) > 0 );

    return 0;
}
