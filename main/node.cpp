
#include "node.hpp"


Node::Node(std::string _log, Node* _next){
  log = _log;
  next = _next;
}

void Node::setLog(std::string _log){
  log = _log;
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