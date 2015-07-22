#include "BufferedReader.h"

BufferedReader::BufferedReader(long bufferSize):DataHolder(bufferSize)
{
    ReadFromDescriptor = &BufferedReader::ReadLength;

}

void BufferedReader::ReadFromSocket(int sock,int &status)
{
    //printf("Read: %d ",sock);

    (this->*ReadFromDescriptor)(sock,status);

    //printf("RedSock..\n");
}

void BufferedReader::ReadLength(int sock,int &status)
{
    int bytesRead;

    int lengthLeft = sizeof(unsigned int)-  (this->m_position - (char*)(this->m_dataBuffer));
    //printf("Len:\n");

    bytesRead = read(sock,this->m_position,lengthLeft);

    if(bytesRead < 1)
    {
        if (errno == EAGAIN)    //No bytes available on this socket to read. Process other connections
        {
            status = 2;
        }
        else //if(errno)
        {
            perror ("read");
            status = 1;
        }

        //printf(" Read Error ");

    }
    /*
    else if(bytesRead == 0) // nothing read
    {
        status = 1;
        printf("Read Nothing\n");
        return;
    }*/
    else
    {
        this->m_position += bytesRead;
        if(this->m_position - (char*)(this->m_dataBuffer) == sizeof(unsigned int))
        {
            this->CheckForBufferSize();
            ReadFromDescriptor = &BufferedReader::ReadData;
            ReadData(sock,status);
        }
    }
}

void BufferedReader::ReadData(int sock,int &status)
{
    int bytesRead = read(sock,this->m_position,*this->m_dataLength
                         - (this->m_position - ((char*)(this->m_dataBuffer) +sizeof(unsigned int) )) );
    //printf("Data:\n");
    if(bytesRead < 1)
    {
        //printf("bytesRead == -1\n");

        if (errno == EAGAIN)    //No bytes available on this socket to read. Process other connections
        {
            status = 2;
            //printf("EAGAIN -1\n");
        }
        else //if(errno)
        {
            //printf("YYYYYYYYYYYYYYYYY %d\n",errno);
            perror ("read");
            status = 1;
        }

        //printf(" Read Error ");
        //return;

    }
    /*else if(bytesRead == 0) // nothing read
    {
        printf("bytesRead == 0\n");
        if (errno == EAGAIN)    //No bytes available on this socket to read. Process other connections
        {
            status = 2;
            printf("EAGAIN 0\n");

        }
        else //if(errno)
        {
            printf("YYYYYYYYYYYYYYYYY Nothing %d\n",errno);
            perror ("read");
            status = 1;
        }

        return;
    }*/
    else
    {
        this->m_position += bytesRead;
        if(*this->m_dataLength - (this->m_position - ((char*)(this->m_dataBuffer) +sizeof(unsigned int))) == 0)
        {
            ReadFromDescriptor = &BufferedReader::ReadLength;
            return;

            //printf("{%u}",*this->m_dataLength);
            ProcessData();
            //printf("%u %s",*this->m_dataLength, ((char*)this->m_dataBuffer)+ sizeof(unsigned int));
            this->ResetPosition();
        }
    }

}

void BufferedReader::ProcessData()
{
    //MUXER.MultiplexData((char*)this->m_dataBuffer);
    //    printf("virtual ProcessData() : %u %s",*this->m_dataLength, ((char*)this->m_dataBuffer)+ sizeof(unsigned int));
    printf("\r\nvirtual ProcessData() : %u",*this->m_dataLength);
    //ProcessManager::processCommand(3,"Kiran");
}
