

#include "list.hpp"

List::List(){     //creates an empty list
  first = 0;
}

List::~List(){    //destroy the whole list
  Node* ptr_next = first;

  while(first){
    ptr_next = ptr_next -> next;
    delete first;
    first = ptr_next;
  }//endwhile
}//endfunc

void List::insert(std::string newLog){    //saves a new log into the list
  Node* aux1 = first;
  Node* aux2 = first;

  if (first == 0){
     first = new Node(newLog, 0);     //creates a new log in case there were'nt any
  }//endif

  else {                      //creates a new log entry and adds to the end of the list
     while (aux2 != 0) {
        aux1 = aux2; 
        aux2 = aux1->getNext();
  }//endif
     aux1->setNext(new Node(newLog, 0)); //last log always points to 0
  }
}

void List::printLog() {
  Node* aux1 = first;

  while (aux1 != 0){
     std::string aux2 = aux1->getLog();
     aux1 = aux1->getNext();
  }//endwhile

  this->~List();      //destroys the list after printing to log console
}