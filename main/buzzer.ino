#include "buzzer.hpp"

#define buzzer  32 


void Buzzer::init(){
  pinMode(buzzer, OUTPUT);
}

void Buzzer::on(){
  digitalWrite(buzzer, HIGH);
}

void Buzzer::off(){
  digitalWrite(buzzer, LOW);
}