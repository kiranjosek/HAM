#include "PeerNode.h"

PeerNode::PeerNode():m_leftNode(NULL),m_rightNode(NULL)
{
    m_socketDescriptor = -1;
}

PeerNode::PeerNode(string nodeName, IPPack* ipPack)
{
    m_nodeName = nodeName;
    m_IPSet = ipPack;
}

void PeerNode::SetLeftPeer(PeerNode* leftNode)
{
    m_leftNode = leftNode;
}

void PeerNode::SetRightPeer(PeerNode* rightNode)
{
    m_rightNode = rightNode;
}

void PeerNode::SetSocketDescriptor(int sockfd)
{
    m_socketDescriptor = sockfd;
}

int PeerNode::GetSocketDescriptor()
{
    return m_socketDescriptor;
}

PeerNode*& PeerNode::GetLeftPeer()
{
    return m_leftNode;
}

PeerNode*& PeerNode::GetRightPeer()
{
    return m_rightNode;
}

void PeerNode::GetAddress(struct sockaddr_in *sin)
{
    memcpy(sin,&m_socketAddress,sizeof(struct sockaddr_in));
}

void PeerNode::SetIp(struct sockaddr_in addr)
{
    memcpy(&m_socketAddress.sin_addr,&addr.sin_addr,sizeof(struct in_addr));
}

void PeerNode::SetAddress(struct sockaddr_in addr)
{
    memcpy(&m_socketAddress,&addr,sizeof(struct sockaddr_in));
}

int PeerNode::IpEqual(struct sockaddr_in addr)
{
    fprintf(stdout,"IpEquiv: %s <=> ", inet_ntoa(m_socketAddress.sin_addr));
    fprintf(stdout,"%s\n", inet_ntoa(addr.sin_addr));
    return (memcmp(&m_socketAddress.sin_addr,&addr.sin_addr,sizeof(struct in_addr)) == 0) ? 1 : 0;
}

string PeerNode::GetNodeName()
{
    return m_nodeName;
}
