
#include "node.hpp"


Node::Node(std::string _log, Node* _next, int _number, std::string _time){
  next = _next;
  number = _number;
  time = _time;
  log = time + number % _log;
}


void Node::setTime(std::string _time){
  time = _time;
}

std::string Node::getTime(){
  return time;
}


void Node::setLog(std::string _log){
  std::string half_log = number % _log;
  log = time;
  log.append(half_log);  
}

std::string Node::getLog(){
  return log;
}

void Node::setNext(Node* _next){
  next = _next;
}

Node* Node::getNext(){
  return next;
}
