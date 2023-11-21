
#include "green.hpp"

#define green  32 


void Green::init(){
  pinMode(green, OUTPUT);
}

void Green::on(){
  digitalWrite(green, HIGH);
}

void Green::off(){
  digitalWrite(green, LOW);
}