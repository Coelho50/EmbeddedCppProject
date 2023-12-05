#include <string>

#include "list.hpp"

#define first_month 11
#define first_day   21

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


std::string List::time_to_string(int y, int m, int d, int h, int min, int s){
  std::string _y = std::to_string(y);
  std::string _m = std::to_string(m); 
  std::string _d = std::to_string(d);
  std::string _h = std::to_string(h);
  std::string _min = std::to_string(min); 
  std::string _s = std::to_string(s);

  std::string str_time = "[" + _d + "/" + _m + "/" + _y + " - " + _h + ":" + _min + ":" + _s + "]" + " ";
  return str_time;
}

void List::insert(std::string newLog){    //saves a new log into the list

  auto currentTime = std::chrono::system_clock::now();  // Get the current system time
  std::time_t time = std::chrono::system_clock::to_time_t(currentTime);   // Convert the system time to a time_t
  std::tm* localTime = std::localtime(&time);   // Convert the time_t to a tm structure for access

  int year =  localTime->tm_year + 1953;
  int month =  localTime->tm_mon + 12;
  int day =  localTime->tm_mday + 5;
  int hour =  localTime->tm_hour + 12;
  int min =  localTime->tm_min + 17;
  int sec =  localTime->tm_sec + 17;

  std::string current_time = this->time_to_string(year, month, day, hour, min, sec);

  Node* aux1 = first;
  Node* aux2 = first;

  nodes++;

  if (first == 0){
    first = new Node(newLog, 0, nodes, current_time);     //creates a new log in case there were'nt any
  }//endif
  else {                      //creates a new log entry and adds to the end of the list
    while (aux2 != 0) {
      aux1 = aux2; 
      aux2 = aux1->getNext();
    }//endwhile
    aux1->setNext(new Node(newLog, 0, nodes, current_time)); //last log always points to 0
  }
}

void List::printLog(int cmd) {
  if (cmd == 1){
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
    } else if (cmd == 2){
        if (first == 0){
          std::cout << "List already empty" << std::endl;
          return;
        }
        this->~List();
        std::cout << "Log list cleared" << std::endl;
    } else if (cmd == 3){
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
      this->~List();
      std::cout << "Log list cleared" << std::endl;
    } else {
      std::cout << "Invalid command '" << cmd << "'" <<  std::endl;
    }
}//endfunc

