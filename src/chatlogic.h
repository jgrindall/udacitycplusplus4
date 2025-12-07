#ifndef CHATLOGIC_H_
#define CHATLOGIC_H_

#include <vector>
#include <string>
#include <memory>
#include "chatgui.h"

// forward declarations
class ChatBot;
class GraphEdge;
class GraphNode;

typedef std::vector<std::unique_ptr<GraphNode>> GraphNodes;
typedef std::vector<GraphEdge*> GraphEdges; 

class ChatLogic
{
private:
    //// STUDENT CODE
    ////

    // data handles (owned)
    GraphNodes _nodes; // owned
    GraphEdges _edges; // owned
    
    std::unique_ptr<ChatBot> _chatBot;


    ////
    //// EOF STUDENT CODE

    // data handles (not owned)
    GraphNode *_currentNode;
    
    ChatBotPanelDialog *_panelDialog;

    // proprietary type definitions
    typedef std::vector<std::pair<std::string, std::string>> TokenList;

    // proprietary functions
    template <typename T>
    void AddAllTokensToElement(std::string tokenID, TokenList &tokens, T &element);

public:
    // constructor / destructor
    ChatLogic();
    ~ChatLogic();

    // getter / setter
    void SetPanelDialogHandle(ChatBotPanelDialog *panelDialog);


    // proprietary functions
    void LoadAnswerGraphFromFile(std::string filename);
    void SendMessageToChatbot(std::string message);
    void SendMessageToUser(std::string message);
    wxBitmap *GetImageFromChatbot();
};

#endif /* CHATLOGIC_H_ */