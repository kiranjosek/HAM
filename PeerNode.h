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


    string m_nodeName;

public:

    PeerNode();
    IPPack* m_IPSet;
    PeerNode(string nodeName, IPPack* ipPack);

    PeerNode*& GetLeftPeer();
    PeerNode*& GetRightPeer();

    void SetLeftPeer(PeerNode* leftNode);
    void SetRightPeer(PeerNode* rightNode);
    string GetNodeName();

    void readRequest();
    void sendHandShakeResponse();//send ip/port of details of right Node
    void readCommand();





};

#endif // PEERNODE_H
