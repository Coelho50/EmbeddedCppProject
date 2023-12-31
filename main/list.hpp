#ifndef LIST_HPP
#define LIST_HPP

#include "node.hpp"
#include <iostream>
#include <Arduino.h>
#include <chrono>
#include <ctime>


class List {
  public:
    Node* first;
    int nodes;    //counts the total of nodes in the list

    List();
    ~List();
    std::string time_to_string(int, int, int, int, int, int); //converts system time to a string
    void insert(std::string); //inserts a new node on list
    void printLog(int); //prints full list
};



#endif