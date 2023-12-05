
#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include "operator.hpp"

class Node {
  public:
    std::string log;
    std::string time;
    int number;   //associates an order of creation for every node
    Node* next;

    Node(std::string, Node*, int, std::string);

    void setTime(std::string);
    std::string getTime(void);

    void setLog(std::string);
    std::string getLog(void);

    void setNext(Node*);
    Node* getNext();
};

#endif