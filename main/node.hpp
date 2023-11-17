
#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include "operator.hpp"

class Node {
  public:
    std::string log;
    int number;   //associates a order od creation for every node
    Node* next;

    Node(std::string, Node*, int);
    void setLog(std::string);
    std::string getLog(void);
    void setNext(Node*);
    Node* getNext();
};

#endif