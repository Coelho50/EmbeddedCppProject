
#include "yellow.hpp"

#define yellow 33

void Yellow::init(){
  pinMode(yellow, OUTPUT);
}

void Yellow::on(){
  digitalWrite(yellow, HIGH);
}

void Yellow::off(){
  digitalWrite(yellow, LOW);
}

