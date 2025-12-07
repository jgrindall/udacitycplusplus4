# Graph edge

  _id
  _keywords string[]
  _childNode : GraphNode   
  _parentNode: GraphNode
    
  SetChild
  GetChildNode
  SetParent

  GetKeywords -> returns keywords
  AddToken? -> push to keywords
    
    
    
# Graph node

  id  
  _answers:string[]
  ChatBot *_chatBot;

  _childEdges  (owned)
  _parentEdges (not owned)

  int GetNumberOfChildEdges
  int GetNumberOfParents

  AddEdgeToParentNode
  AddEdgeToChildNode

  GetChildEdgeAtIndex

  MoveChatbotHere(std::unique_ptr<ChatBot> chatbot);
  MoveChatbotToNewNode(GraphNode *newNode);

  GetAnswers

  AddToken (push into _answers)




# chat gui

ignore




