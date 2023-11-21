
#include "red.hpp"

#define red    14

void Red::init(){
  pinMode(red, OUTPUT);
}

void Red::on(){
  digitalWrite(red, HIGH);
}

void Red::off(){
  digitalWrite(red, LOW);
}