#define yellow 33
#define green  32 
#define red    14 
#define buzzer 12


#include "peripherals.hpp"



void Peripherals::peripherals_init(){
  pinMode(33, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(12, OUTPUT);
}

void standby(){
  digitalWrite(yellow, HIGH);
  delay(1000);
  while(!reader.PICC_IsNewCardPresent());
  digitalWrite(yellow, LOW);
}

void Peripherals::activate_green(){
  digitalWrite(32, HIGH);
}
void Peripherals::deactivate_green(){
  digitalWrite(32, LOW);
}
void Peripherals::aborted_activation(){
  for (byte i = 0; i < 3; i++){
    digitalWrite(14,HIGH);
    delay(100);
    digitalWrite(14,LOW);
  }
}
void Peripherals::alarm_on(){
  while(!reader.PICC_IsNewCardPresent()){
    digitalWrite(33,HIGH);
    digitalWrite(32,HIGH);
    digitalWrite(14,HIGH);
    digitalWrite(12,HIGH);

    delay(100);

    digitalWrite(33,LOW);
    digitalWrite(32,LOW);
    digitalWrite(14,LOW);
    digitalWrite(12,LOW);
  }
  
  Serial.println("\nAlarm deactivated by card");
  Serial.println("Entering stanby mode");
  delay(2000);
}