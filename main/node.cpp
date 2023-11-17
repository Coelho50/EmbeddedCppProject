
#include "node.hpp"


Node::Node(std::string _log, Node* _next, int _number){
  next = _next;
  number = _number;
  log = number + _log;
}

void Node::setLog(std::string _log){
  log = number + _log;
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
