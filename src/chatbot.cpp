#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <memory>

#include "chatlogic.h"
#include "graphnode.h"
#include "graphedge.h"
#include "chatbot.h"
#include "leven.h"

// constructor WITHOUT memory allocation
ChatBot::ChatBot()
{
    // invalidate data handles
    _image = nullptr;
    _chatLogic = nullptr;
    _rootNode = nullptr;
    _currentNode = nullptr;
}

// constructor WITH memory allocation
ChatBot::ChatBot(std::string filename)
{
    std::cout << "ChatBot Constructor" << std::endl;
    
    // invalidate data handles
    _chatLogic = nullptr;
    _rootNode = nullptr;
 _currentNode = nullptr;
    // load image into heap memory
    _image = std::make_unique<wxBitmap>(filename, wxBITMAP_TYPE_PNG);
}

ChatBot::ChatBot(const ChatBot &source) // copy constructor
{
    std::cout << "ChatBot Copy Constructor" << std::endl;

    if (source._image != nullptr) {
        wxBitmap img = *source._image;
        _image = std::unique_ptr<wxBitmap>( new wxBitmap(img));
    }

    _chatLogic = source._chatLogic;
    _currentNode = source._currentNode;
    _rootNode = source._rootNode;
}

ChatBot& ChatBot::operator=(const ChatBot& other) { 
    std::cout << "ChatBot Copy Assignment Operator" << std::endl;

    if (other._image != nullptr) {
        wxBitmap img = *other._image;
        _image = std::unique_ptr<wxBitmap>( new wxBitmap(img));
    }

    _chatLogic = other._chatLogic;
    _currentNode = other._currentNode;
    _rootNode = other._rootNode;

    return *this;

}

ChatBot::ChatBot(ChatBot&& other) {
    std::cout << "ChatBot Move Constructor" << std::endl;

      _image = std::move(other._image);
      _chatLogic = other._chatLogic;
      _rootNode = other._rootNode;
      _currentNode = other._currentNode;

      other._chatLogic = nullptr;
      other._rootNode = nullptr;
      other._currentNode = nullptr;

}

ChatBot& ChatBot::operator=(ChatBot&& other) {
    std::cout << "ChatBot Move Assignment Operator" << std::endl;
    
    _image = std::move(other._image);
    _chatLogic = other._chatLogic;
    _rootNode = other._rootNode;
    _currentNode = other._currentNode;

    other._chatLogic = nullptr;
    other._rootNode = nullptr;
    other._currentNode = nullptr;

    return *this;
}

ChatBot::~ChatBot()
{
    std::cout << "ChatBot Destructor" << std::endl;
}

void ChatBot::ReceiveMessageFromUser(std::string message)
{
    // loop over all edges and keywords and compute Levenshtein distance to query
    typedef std::pair<GraphEdge *, int> EdgeDist;
    std::vector<EdgeDist> levDists; // format is <ptr,levDist>

    for (size_t i = 0; i < _currentNode->GetNumberOfChildEdges(); ++i)
    {
        GraphEdge *edge = _currentNode->GetChildEdgeAtIndex(i);
        for (auto keyword : edge->GetKeywords())
        {
            int dist = Leven::ComputeLevenshteinDistance(keyword, message);
            EdgeDist ed{edge, dist};
            levDists.push_back(ed);
        }
    }

    // select best fitting edge to proceed along
    GraphNode *newNode;
    if (levDists.size() > 0)
    {
        // sort in ascending order of Levenshtein distance (best fit is at the top)
        std::sort(levDists.begin(), levDists.end(), [](const EdgeDist &a, const EdgeDist &b) { return a.second < b.second; });
        newNode = levDists.at(0).first->GetChildNode(); // after sorting the best edge is at first position
    }
    else
    {
        // go back to root node
        newNode = _rootNode;
    }

    // tell current node to move chatbot to new node
    _currentNode->MoveChatbotToNewNode(newNode);
}

void ChatBot::SetCurrentNode(GraphNode *node)
{
    _currentNode = node;

    // Update ChatLogic's current node FIRST before sending messages
    if (_chatLogic != nullptr) {
        _chatLogic->SetCurrentNode(node);
    }

    std::vector<std::string> answers = _currentNode->GetAnswers();
    std::mt19937 generator(int(std::time(0)));
    std::uniform_int_distribution<int> dis(0, answers.size() - 1);
    std::string answer = answers.at(dis(generator));

    _chatLogic->SendMessageToUser(answer);
}
