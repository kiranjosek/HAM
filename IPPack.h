#ifndef IPPACK_H
#define IPPACK_H

struct IPPack
{
    char m_ip[64];
    int m_port;
    IPPack()
    {
        memset(m_ip,'\0',64);
        m_port = -1;
    }

    IPPack(char * ip, int port)
    {
        memset(m_ip,'\0',64);
        SetIPPack(ip,port);
    }

    void SetIPPack(char* ip, int port)
    {
        if(ip)
            memcpy(m_ip,ip,strlen(ip)+1);

        m_port = port;
    }

    void show()
    {
        printf("IPPack: IP-> %s PORT->%d\n",m_ip,m_port);
    }
};

#endif // IPPACK_H
