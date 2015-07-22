#include "DataMultiplexer.h"
#include <iostream>
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


DataMultiplexer::DataMultiplexer()
{
    //cerr <<"\n#####################################################################################\n";
}

void DataMultiplexer::MultiplexData(char* buff)
{
    pthread_mutex_lock(&lock);

    vector<int> ::iterator iter = m_clientList.begin();
    vector<int> ::iterator iterEnd = m_clientList.end();

    for(; iter != iterEnd; ++iter)
    {
        //printf("Sending Data\n");
        m_bufferWriter.WriteToSocket(*iter,buff);
    }

    pthread_mutex_unlock(&lock);

}


void DataMultiplexer::RemoveSubscriberSocket(int sock)
{
    pthread_mutex_lock(&lock);

    //m_clientList.erase(remove(m_clientList.begin(),m_clientList.end(),sock),m_clientList.end());
    vector<int>::iterator iter = m_clientList.begin();

    for(unsigned i = 0; i< m_clientList.size(); ++i)
    {
        if(m_clientList.at(i) == sock)
        {
            m_clientList.erase(iter);
            break;
        }
        ++iter;
    }

    pthread_mutex_unlock(&lock);
}

void DataMultiplexer::AddSubscriberSocket(int sock)
{
    pthread_mutex_lock(&lock);
    m_clientList.push_back(sock);
    pthread_mutex_unlock(&lock);

}
