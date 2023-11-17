#include <string>


#include "list.hpp"
#include <iostream>

List::List(){     //creates an empty list
  first = 0;
  nodes = 0;
}

List::~List(){    //destroy the whole list
  Node* ptr_next = first;

  while(first){
    ptr_next = ptr_next -> next;
    delete first;
    first = ptr_next;
  }//endwhile

  nodes = 0;
}//endfunc

void List::insert(std::string newLog){    //saves a new log into the list
  Node* aux1 = first;
  Node* aux2 = first;

  nodes++;
  if (first == 0){
     first = new Node(newLog, 0, nodes);     //creates a new log in case there were'nt any
  }//endif

  else {                      //creates a new log entry and adds to the end of the list
     while (aux2 != 0) {
        aux1 = aux2; 
        aux2 = aux1->getNext();
  }//endif
     aux1->setNext(new Node(newLog, 0, nodes)); //last log always points to 0
  }
}

void List::printLog() {
  Node* aux1 = first;

  if (first == 0){
    std::cout << "No logs available" << std::endl;
    return;
  }
  std::cout << " " << std::endl;
  std::cout <<"---------- Log entries -------------" << std::endl;
  while (aux1 != 0){
    std::string aux2 = aux1->getLog();
    std::cout << aux2 << std::endl;
    aux1 = aux1->getNext();
  }//endwhile
  std::cout << "Total of entries: " << nodes << std::endl; 
  std::cout <<"------------------------------------" << std::endl;
  
  this->~List();
}

