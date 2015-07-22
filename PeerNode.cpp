#include "PeerNode.h"

PeerNode::PeerNode():m_leftNode(NULL),m_rightNode(NULL)
{
    m_IPSet = NULL;
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

PeerNode*& PeerNode::GetLeftPeer()
{
    return m_leftNode;
}

PeerNode*& PeerNode::GetRightPeer()
{
    return m_rightNode;
}

string PeerNode::GetNodeName()
{
    return m_nodeName;
}
