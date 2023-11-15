
//yellow = 33
//green = 32
//red = 14
//buzzer = 12

#include "PIR.hpp"
#include "peripherals.hpp"


PRESENCE presence;

PIR::PIR(){}

PIR::~PIR(){}



bool PIR::pir_init(byte pin_to_set){
  bool confirmation = false;

  digital_pin = pin_to_set; //------> setting PIRs digital pin

  Serial.println("\nActivating alarm in 120 seconds");
  Serial.println("To cancel this action, hold your tag in front of the reader for 1 full second.\n");

  delay(1000);

  int i = 120; 
  //for loop not working?

  while (i>0){   //-----> PRINT REMAINING TIME
    i--;

    if (i%2 == 0){
      LEDS.activate_green();
    }
    else{
      LEDS.deactivate_green();
    }

    if (i%10 == 0){
    Serial.println(String("Seconds remaining: ") + i);
    }//endif



    delay(750);    //-----------> DEACTIVATE FOR TESTING

    if (reader.PICC_IsNewCardPresent()){
      LEDS.deactivate_green();
      Serial.println("Aborting system activation");
      delay(2000);
      Serial.println("System activation aborted, entering standby");
      return confirmation;
      break;     //break not working??
    }//endif

  }//endwhile
  pinMode(digital_pin, INPUT);

  confirmation = true;

  return confirmation;
}//endfunc




PRESENCE PIR::motion_alarm(){
  int time = 0;
  presence = UNAUTHORIZED;

  while (true){

    if (digitalRead(4) == HIGH){
      Serial.print("Movement detected\n");
      while (time <=1000){ //starts counter waiting for card to authorize entrance
        if (reader.PICC_IsNewCardPresent()){
          Serial.print("\nEntrance authorized, deactivatin motion sensor");
          LEDS.deactivate_green();
          presence = AUTHORIZED;
          delay(1000);
          return presence;
        } 
        if (time%100 == 0){
          int _time = 10 - time/100;
          Serial.print(_time);
          Serial.print(", ");
        }
        time++;
      }//endwhile
      if (presence == UNAUTHORIZED){
        Serial.println("\nUNAUTHORIZED ENTRANCE DETECTED");
        LEDS.alarm_on();
        return presence;
      }//endif
    }//endif
  }//endwhile
}//endfunction