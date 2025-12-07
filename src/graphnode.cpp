
#include <memory>
#include <iostream>

#include "graphedge.h"
#include "graphnode.h"

GraphNode::GraphNode(int id)
{
    _id = id;
}

GraphNode::~GraphNode()
{
    _chatBot = nullptr; // invalidate pointer to chatbot
}

void GraphNode::AddToken(std::string token)
{
    _answers.push_back(token);
}

void GraphNode::AddEdgeToParentNode(GraphEdge *edge)
{
    _parentEdges.push_back(edge);
}

void GraphNode::AddEdgeToChildNode(std::unique_ptr<GraphEdge> edge)
{
    _childEdges.push_back(std::move(edge));
}


void GraphNode::MoveChatbotHere(ChatBot *chatbot)
{
    std::cout << "MoveChatbotHere: Creating unique_ptr" << std::endl;
     _chatBot = chatbot;
    std::cout << "MoveChatbotHere: About to call SetCurrentNode" << std::endl;
    _chatBot->SetCurrentNode(this);
    std::cout << "MoveChatbotHere: Done" << std::endl;
}


void GraphNode::MoveChatbotToNewNode(GraphNode *newNode)
{
    std::cout << "MoveChatbotToNewNode: Moving chatbot to new node" << std::endl;
    newNode->MoveChatbotHere(_chatBot);
    _chatBot = nullptr; // invalidate pointer to chatbot
}

////
//// EOF STUDENT CODE

GraphEdge *GraphNode::GetChildEdgeAtIndex(int index)
{
    //// STUDENT CODE
    ////
    return _childEdges[index].get();

    ////
    //// EOF STUDENT CODE
}