#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"


class List {
  public:
    Node* first;
    int nodes;    //counts the total of nodes in the list

    List();
    ~List();
    void insert(std::string);
    void printLog();
};



#endif