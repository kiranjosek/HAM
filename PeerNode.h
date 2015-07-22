#ifndef PEERNODE_H
#define PEERNODE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>

#include "IPPack.h"

using namespace std;

class PeerNode
{
    PeerNode* m_leftNode;
    PeerNode* m_rightNode;

    struct sockaddr_in m_socketAddress;
    int m_socketDescriptor;
    string m_nodeName;

public:

    PeerNode();
    struct IPPack* m_IPSet;
    PeerNode(string nodeName, IPPack* ipPack);

    PeerNode*& GetLeftPeer();
    PeerNode*& GetRightPeer();

    void SetLeftPeer(PeerNode* leftNode);
    void SetRightPeer(PeerNode* rightNode);
    void SetSocketDescriptor(int sockfd);
    int  GetSocketDescriptor();

    int  IpEqual(struct sockaddr_in addr);
    void SetIp(struct sockaddr_in addr);
    void SetAddress(struct sockaddr_in addr);
    void GetAddress(struct sockaddr_in *sin);
    string GetNodeName();

    void readRequest();
    void sendHandShakeResponse();//send ip/port of details of right Node
    void readCommand();





};

#endif // PEERNODE_H
