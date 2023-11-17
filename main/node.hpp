
#ifndef NODE_HPP
#define NODE_HPP

#include <string>

class Node {
  public:
    std::string log;
    Node* next;

    Node(std::string, Node*);
    void setLog(std::string);
    std::string getLog(void);
    void setNext(Node*);
    Node* getNext();
};



#endif