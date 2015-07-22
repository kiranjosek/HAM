#include <ctime>
#include <iostream>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include <sys/time.h>
#include <map>
#include <typeinfo>

using namespace std;
#include "SocketWatcher.h"
//#include "MemoryMaster.h"
#include "SocketClass.h"
#include "SubscriberServer.h"
#include "RegisterServer.h"
#include <pthread.h>
#include "IPPack.h"
#include "VirtualPeerLoop.h"
#include "SortedIntegerArray.h"
#include "PeerWatcher.h"
#include "HAMCore.h"
/*
#define SEC
#define THR
*/

/*
void *clientReceiver(void *arg)
{
#ifdef THR
    //RegisterServer sockCl("127.0.0.1",4040);
    //sockCl.StartWatcher();
    SocketClass skcl;
    int sockFd = skcl.CreateClientSocket("127.0.0.1",4040);
    MUXER.AddSubscriberSocket(sockFd);
    return 0;
#elif defined SEC
    RegisterServer sockCl(4042);
    sockCl.StartWatcher();
#else
    RegisterServer sockCl(4041);
    sockCl.StartWatcher();
#endif
    return 0;
}
*/

extern  PeerWatcher PEERWATCHER;
/*
void *peerMonitor(void *arg)
{

    //    IPPack* pack1 = new IPPack("127.0.0.1",4040);

    pthread_t tid1;

    int err1 = pthread_create(&tid1, NULL, reconnectClient, new IPPack("127.0.0.1",4040));
    if (err1 != 0)
    {
        //        cerr <<("can't create thread");
        exit(err1);
    }

    //    IPPack* pack2 = new IPPack("127.0.0.1",4041);


    pthread_t tid2;

    int err2 = pthread_create(&tid2, NULL, reconnectClient, new IPPack("127.0.0.1",4041));
    if (err2 != 0)
    {
        //        cerr <<("can't create thread");
        exit(err2);
    }


    //    PEERWATCHER.AddSocketToPeerWatch("127.0.0.1",4040);
    //    PEERWATCHER.AddSocketToPeerWatch("127.0.0.1",4041);
    PEERWATCHER.StartWatcher();
    //    reconnectClient(new IPPack("127.0.0.1",4041));

    //    IPPack* pack3 = new IPPack("127.0.0.1",4042);

    //    pthread_t tid3;

    //    int err3 = pthread_create(&tid3, NULL, reconnectClient, pack3);
    //    if (err3 != 0)
    //    {
    //        //        cerr <<("can't create thread");
    //        exit(err3);
    //    }


    sleep(10);


    return 0;
}
*/

int main(int argc, char *argv[])
{
    signal(SIGPIPE,SIG_IGN);

    if(argc < 2)
        return 0;
    /*
    {
        SocketClass ss;

        int m_sock = ss.CreateServerSocket(0);
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    if(getsockname(m_sock,(struct sockaddr*)&addr,&addrlen) == 0)
       cerr <<"ERROR"  ;// Self.SetIp(addr);
    }

    struct hostent *h;
    char hostname[128];
    char *hostdots[2]={0,0}, *hdptr=hostname;

    if (gethostname(hostname, 128) == -1) return -1;
    //	  printf("%s\n", hostname);
    while(*hdptr) if(*hdptr++ == '.')
    {
        hostdots[0] = hostdots[1];
        hostdots[1] = hdptr;
    }
    if (hostdots[0] == 0) return -1;
    //	  printf("%s\n", hostdots[0]);
    if ((h = gethostbyname(hostdots[0])) == NULL) return -1;
    //printf("Host domain  : %s\n", h->h_name);
    //printf("IP Address : %s\n", inet_ntoa(*((struct in_addr *)h->h_addr)));
    //memcpy(&Self.m_sin.sin_addr,h->h_addr,sizeof(struct in_addr));
    return 0;

*/
    /*
    cerr << "StartTimer";
    //MemoryMaster* mm = MEMORYMASTER;
    int size = 1024*1024*10; //1024*507 +1012;

    time_t tt= time(NULL);
    for(long i=0; i< 10000000; ++i)
    {
#if 1
        MemoryBlock* memBlock = MEMORYMASTER->AllocateNewMemory(size);
        char* ch = memBlock->m_memoryBase+(char*)MEMORYMASTER->GetMemoryBase();
        MEMORYMASTER->FreeMemoryWithBase(ch);
#else
        char* cc = new char[size];
        delete []cc;
#endif
        if(i%1000000==0)
            cerr<<i;

    }

    cerr <<"Taken "<<time(NULL) - tt <<endl;

    return 0;
*/
/*
#ifdef THR

    pthread_t tid;

    int err = pthread_create(&tid, NULL, clientReceiver, 0);
    if (err != 0)
    {
        cerr <<("can't create thread");
        exit(err);
    }


    SubscriberServer sockCl("127.0.0.1",4042); //4041

    sockCl.StartWatcher();

#elif defined SEC

    pthread_t tid;

    int err = pthread_create(&tid, NULL, clientReceiver, 0);
    if (err != 0)
    {
        cerr <<("can't create thread");
        exit(err);
    }



    SubscriberServer sockCl("127.0.0.1",4041); //4041

    sockCl.StartWatcher();

#else
    */
    /*
    pthread_t tid;
    int err = pthread_create(&tid, NULL, clientReceiver, 0);
    if (err != 0)
    {
        cerr <<("can't create thread");
        exit(err);
    }
*/

    //setitimer();
    //tzset();
    //    time_t tt;///=time(NULL);
    //    ctime(&tt);
    //    cerr << "timezone " << timezone << endl;
    //    cerr << "tzname 0 " <<*tzname <<endl;
    //    cerr << "tzname 1 " <<*tzname[1] <<endl;


    //    int gettimeofday(struct timeval *tv, struct timezone *tz);
    /*
    struct timeval tvv;
    struct timezone tzz;

    gettimeofday(&tvv,&tzz);
*/
    //    #define DEBUG_PANIC(p) CLogging::Debuglogf("Debug Marker (%s)- :: %s() in file: %s (%d)",p,__func__,__FILE__,__LINE__)


//    fprintf(stderr,"%s %s %d %s %d %d %s %s\n",__FILE__,__FUNCTION__,__LINE__,__PRETTY_FUNCTION__,__STDC__,__cplusplus,__DATE__,__TIME__);
    /*
FILE
LINE
DATE
TIME
STDC
STDC_VERSION
STDC_HOSTED
_cplusplus
OBJC
ASSEMBLER
*/
    /*
    SortedIntegerArray sia(10);

    sia.insertValue(10);
    */
    /*
    sia.insertValue(1);

    sia.insertValue(15);

    sia.insertValue(10);

    sia.insertValue(10);
*/


    //    return 0;
    map<string,IPPack*> ippackSet;
    ippackSet["Node1"] = new IPPack("0.0.0.0",4040);
    ippackSet["Node2"] = new IPPack("0.0.0.0",7801);
    ippackSet["Node3"] = new IPPack("0.0.0.0",7802);
    ippackSet["Node4"] = new IPPack("0.0.0.0",7803);
    ippackSet["Node5"] = new IPPack("0.0.0.0",7804);
/*
    VirtualPeerLoop pc;
    pc.SetPeerNode(ippackSet,"Node4");
    pc.ShowPeerLoop();
    pc.AddPeerToRightOfNode(pc.GetConnectedNode()->GetNodeName(),new PeerNode("NewNode", new IPPack("0.0.0.0",9996)));

    return 0;
*/
    PEERWATCHER.SetPeerNode(ippackSet,argv[1]);

    HAMCore ham;
    ham.HAMStart();

    //    reconnectClient(PEERWATCHER.getConnectedNode()->m_IPSet);



    //    int sock = pc.GetSocketDescriptor();
    /*
    SocketClass sc;
    sc.SetSocketDescriptor(sock);
    sc.BytesAvailable();
*/


    /*
    pc.SetPeerNode(ippackSet,1);
    pc.ShowPeerLoop();
*/
    /*
    PeerSocketClass pWatch;
    pWatch.AddSocketToPeerWatch("127.0.0.1",4040);
    pWatch.AddSocketToPeerWatch("127.0.0.1",4041);
    pWatch.StartWatcher();
*/
    /*
    pthread_t tid;

    int err = pthread_create(&tid, NULL, peerMonitor, 0);
    if (err != 0)
    {
        cerr <<("can't create thread");
        exit(err);
    }

    sleep(10);

    IPPack* pack3 = new IPPack("127.0.0.1",4042);

    pthread_t tid3;

    int err3 = pthread_create(&tid3, NULL, reconnectClient, pack3);

    if (err3 != 0)
    {
        //        cerr <<("can't create thread");
        exit(err3);
    }

    cerr << "Size(): " << sizeof(SocketBase) << endl;
    cerr << "Size(): " << sizeof(SocketClass) << endl;
    cerr << "Size(): " << sizeof(ClientSocketClass) << endl;
    cerr << "Size(): " << sizeof(ServerSocketClass) << endl;

    ServerSocketClass ssc;
    int x = ssc.CreateServerSocket(2222);

    SocketClass sc1;
    sc1.SetSocketDescriptor(x);
*/

    PEERWATCHER.StartWatcher();


    while(1)
        sleep(3);

    cerr <<"exit....\n"    ;



    //    return 0;
#if 0
    //    SubscriberServer sockCl(4040);
    //    sockCl.StartWatcher();

#endif
    return 0;
}

/*
int main(int argc, char *argv[])
{



    MemoryBlock*m1=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m1);
    //FSize 54
    MemoryBlock*m2=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m2);
    //FSize 107
    MemoryBlock*m3=MEMORYMASTER->allocateNewMemory(108);
    MEMORYMASTER->freeMemoryBlock(m3);
    //FSize 108
    MemoryBlock*m4=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m4);
    //FSize 110
    MemoryBlock*m5=MEMORYMASTER->allocateNewMemory(126);
    MemoryBlock*m6=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m6);
    //FSize 54
    MemoryBlock*m7=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m7);
    //FSize 107
    MemoryBlock*m8=MEMORYMASTER->allocateNewMemory(108);
    MEMORYMASTER->freeMemoryBlock(m8);
    //FSize 108
    MemoryBlock*m9=MEMORYMASTER->allocateNewMemory(110);
    MemoryBlock*m10=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m10);
    //FSize 54
    MemoryBlock*m11=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m9);
    //FSize 110
    MemoryBlock*m12=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m11);
    //FSize 107
    MemoryBlock*m13=MEMORYMASTER->allocateNewMemory(108);
    MemoryBlock*m14=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m14);
    //FSize 54
    MemoryBlock*m15=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m13);
    //FSize 108
    MemoryBlock*m16=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m16);
    //FSize 110
    MemoryBlock*m17=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m15);
    //FSize 107
    MemoryBlock*m18=MEMORYMASTER->allocateNewMemory(108);
    MemoryBlock*m19=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m19);
    //FSize 54
    MemoryBlock*m20=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m18);
    //FSize 108
    MemoryBlock*m21=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m21);
    //FSize 110
    MemoryBlock*m22=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m20);
    //FSize 107
    MemoryBlock*m23=MEMORYMASTER->allocateNewMemory(108);
    MemoryBlock*m24=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m24);
    //FSize 54
    MemoryBlock*m25=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m23);
    //FSize 108
    MemoryBlock*m26=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m26);
    //FSize 110
    MemoryBlock*m27=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m25);
    //FSize 107
    MemoryBlock*m28=MEMORYMASTER->allocateNewMemory(108);
    MEMORYMASTER->freeMemoryBlock(m28);
    //FSize 108
    MemoryBlock*m29=MEMORYMASTER->allocateNewMemory(110);
    MemoryBlock*m30=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m30);
    //FSize 54
    MemoryBlock*m31=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m29);
    //FSize 110
    MemoryBlock*m32=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m31);
    //FSize 107
    MemoryBlock*m33=MEMORYMASTER->allocateNewMemory(108);
    MemoryBlock*m34=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m34);
    //FSize 54
    MemoryBlock*m35=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m33);
    //FSize 108
    MemoryBlock*m36=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m36);
    //FSize 110
    MemoryBlock*m37=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m35);
    //FSize 107
    MemoryBlock*m38=MEMORYMASTER->allocateNewMemory(108);
    MEMORYMASTER->freeMemoryBlock(m38);
    //FSize 108
    MemoryBlock*m39=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m39);
    //FSize 110
    MemoryBlock*m40=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m17);
    //FSize 126);
    MEMORYMASTER->freeMemoryBlock(m22);
    //FSize 126);
    MEMORYMASTER->freeMemoryBlock(m12);
    //FSize 126
    MemoryBlock*m41=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m41);
    //FSize 54
    MemoryBlock*m42=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m42);
    //FSize 107
    MemoryBlock*m43=MEMORYMASTER->allocateNewMemory(108);
    MEMORYMASTER->freeMemoryBlock(m43);
    //FSize 108
    MemoryBlock*m44=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m44);
    //FSize 110
    MemoryBlock*m45=MEMORYMASTER->allocateNewMemory(126);
    MemoryBlock*m46=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m46);
    //FSize 54
    MemoryBlock*m47=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m47);
    //FSize 107
    MemoryBlock*m48=MEMORYMASTER->allocateNewMemory(108);
    MEMORYMASTER->freeMemoryBlock(m48);
    //FSize 108
    MemoryBlock*m49=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m49);
    //FSize 110
    MemoryBlock*m50=MEMORYMASTER->allocateNewMemory(126);
    MemoryBlock*m51=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m51);
    //FSize 54
    MemoryBlock*m52=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m52);
    //FSize 107
    MemoryBlock*m53=MEMORYMASTER->allocateNewMemory(108);
    MemoryBlock*m54=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m54);
    //FSize 54
    MemoryBlock*m55=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m53);
    //FSize 108
    MemoryBlock*m56=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m56);
    //FSize 110
    MemoryBlock*m57=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m55);
    //FSize 107
    MemoryBlock*m58=MEMORYMASTER->allocateNewMemory(108);
    MemoryBlock*m59=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m59);
    //FSize 54
    MemoryBlock*m60=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m58);
    //FSize 108
    MemoryBlock*m61=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m61);
    //FSize 110
    MemoryBlock*m62=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m60);
    //FSize 107
    MemoryBlock*m63=MEMORYMASTER->allocateNewMemory(108);
    MEMORYMASTER->freeMemoryBlock(m63);
    //FSize 108
    MemoryBlock*m64=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m64);
    //FSize 110
    MemoryBlock*m65=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m32);
    //FSize 126);
    MEMORYMASTER->freeMemoryBlock(m37);
    //FSize 126
    MemoryBlock*m66=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m66);
    //FSize 54
    MemoryBlock*m67=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m67);
    //FSize 107
    MemoryBlock*m68=MEMORYMASTER->allocateNewMemory(108);
    MEMORYMASTER->freeMemoryBlock(m68);
    //FSize 108;
    MemoryBlock*m69=MEMORYMASTER->allocateNewMemory(110);
    MemoryBlock*m70=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m70);
    //FSize 54
    MemoryBlock*m71=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m69);
    //FSize 110
    MemoryBlock*m72=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m71);
    //FSize 107
    MemoryBlock*m73=MEMORYMASTER->allocateNewMemory(108);
    MemoryBlock*m74=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m74);
    //FSize 54
    MemoryBlock*m75=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m73);
    //FSize 108
    MemoryBlock*m76=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m76);
    //FSize 110
    MemoryBlock*m77=MEMORYMASTER->allocateNewMemory(126);
    MEMORYMASTER->freeMemoryBlock(m75);
    //FSize 107
    MemoryBlock*m78=MEMORYMASTER->allocateNewMemory(108);
    MEMORYMASTER->freeMemoryBlock(m78);
    //FSize 108
    MemoryBlock*m79=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m79);
    //FSize 110
    MemoryBlock*m80=MEMORYMASTER->allocateNewMemory(126);
    MemoryBlock*m81=MEMORYMASTER->allocateNewMemory(54);
    MEMORYMASTER->freeMemoryBlock(m81);
    //FSize 54
    MemoryBlock*m82=MEMORYMASTER->allocateNewMemory(107);
    MEMORYMASTER->freeMemoryBlock(m82);
    //FSize 107
    MemoryBlock*m83=MEMORYMASTER->allocateNewMemory(108);
    MEMORYMASTER->freeMemoryBlock(m83);
    //FSize 108
    MemoryBlock*m84=MEMORYMASTER->allocateNewMemory(110);
    MEMORYMASTER->freeMemoryBlock(m84);
    //FSize 110
    cerr << "\nZZZZZZZZZZZZ\n";
    MemoryBlock*m85=MEMORYMASTER->allocateNewMemory(126);

    cerr <<"\nXXXXXXXXXXX\n";


    return 0;
}
*/
