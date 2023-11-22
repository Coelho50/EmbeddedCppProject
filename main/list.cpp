#include <string>

#include "list.hpp"

#define first_month 11
#define first_day   21

List::List(){     //creates an empty list
  first = 0;
  nodes = 0;
}

List::~List(){    //destroy the whole list
  nodes = 0;

  Node* ptr_next = first;
  while(first){
    ptr_next = ptr_next -> next;
    delete first;
    first = ptr_next;
  }//endwhile
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
  int month =  localTime->tm_mon + first_month;
  int day =  localTime->tm_mday + first_day;
  int hour =  localTime->tm_hour + 15;
  int min =  localTime->tm_min + 32;
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
  if (cmd == 0){
    this->~List();
    std::cout << "Log list cleared" << std::endl;

  } else if (cmd == 1){
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
      while(Serial.available()) {     //clears serial entrys 
        if(Serial.read() == '\n') break; 
        Serial.read();
      }

      std::cout << "Enter the time frame (in days) to print: "
      int time = 30;
      while(!Serial.available() and time >= 0){
          time--;
          delay(1000);
      }
      
      if (time >= 0){
        int days = Serial.read();
            Node* aux1 = first;
        if (first == 0){
          std::cout << "No logs available" << std::endl;
          return;
        }

        int current_day =  localTime->tm_mday + first_day;
        int print_until = current_day
        int entries = 0;
        std::cout << " " << std::endl;
        std::cout <<"---------- Log entries -------------" << std::endl;
        while (aux1 != 0){
          std::string aux2 = aux1->getLog();
          std::cout << aux2 << std::endl;
          aux1 = aux1->getNext();
          entries++;
        }//endwhile
        std::cout << "Total of entries in the last " << days << " days: " << entries << std::endl; 
        std::cout <<"------------------------------------" << std::endl;
      }
  }
}

