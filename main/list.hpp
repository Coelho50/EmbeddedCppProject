#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"


class List {
  public:
    Node* first;

    List();
    ~List();
    void insert(std::string);
    void printLog();
};



#endif