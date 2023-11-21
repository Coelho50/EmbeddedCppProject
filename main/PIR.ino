

#include "PIR.hpp"
#include "peripherals.hpp"


PRESENCE presence;
Yellow yellow;
Green green;
Red red;
Buzzer buzzer;
Peripherals *ptr;         //using polimorfism to call the functions of the LEDs
List log_list;


template<typename T>
bool PIR<T>::pir_init(T pin_to_set){    //initializes motion sensor and all peripherals
  bool confirmation = false;

  ptr = &yellow; ptr->init();
  ptr = &green; ptr->init();
  ptr = &red; ptr->init();
  ptr = &buzzer; ptr->init();


  digital_pin = pin_to_set;                 //setting PIRs digital pin

  Serial.println("\nActivating alarm in 120 seconds");
  Serial.println("To cancel this action, hold your tag in front of the reader for 1 full second.\n");

  delay(1000);            //delay used so that the initialization isn't immediatly cancelled

  int i = 120; 
  //for loop not working

  while (i>0){                                 //waits 120seconds before activating motion sensor (for loop doesnt work while using MFRC library)
    i--;  

    if (i%2 == 0){ //blinks green LED
      ptr = &green; 
      ptr->on();
    }
    else{
      ptr->off();
    }

    if (i%10 == 0){
    Serial.println(String("Seconds remaining: ") + i); //Prints remaining time every 10 seconds
    }//endif

    //delay(1000);    //-----------> DEACTIVATE FOR TESTING



    if (reader.PICC_IsNewCardPresent()){    //makes so the activation gets cancelled if a card/tag is detected
      ptr = &green;
      ptr->off();                           //making sure the green LED is deactivated
      Serial.println("\nAborting system activation");
      delay(2000);
      Serial.println("System activation aborted, entering standby");
      return confirmation;
      break;    
    }//endif

  }//endwhile

  pinMode(digital_pin, INPUT); //declares PIR's digital pin as an input

  confirmation = true; //confirmation of PIR activation

  return confirmation;
}//endfunc


template<typename T>
PRESENCE PIR<T>::motion_alarm(){
  int time = 0;
  presence = UNAUTHORIZED;

  while (true){

    if (digitalRead(4) == HIGH){
      Serial.print("Movement detected\n");
      while (time <=1000){                                               //starts counter waiting for card to authorize entrance
        if (reader.PICC_IsNewCardPresent()){
          Serial.print("\nEntrance authorized, deactivatin motion sensor");
          ptr = &green;
          ptr->off();
          presence = AUTHORIZED;

          log_list.insert("Authorized entrance detected");
          delay(1000);
          return presence;                //returns AUTHORIZED
        } 
        if (time%100 == 0){               //prints remaining time to serial every 10 seconds
          int _time = 10 - time/100;
          Serial.print(_time);
          Serial.print(", ");
        }
        time++;
      }//endwhile

      if (presence == UNAUTHORIZED){
        Serial.println("\nUNAUTHORIZED ENTRANCE DETECTED");
        log_list.insert("UNAUTHORIZED ENTRANCE DETECTED");
        this->alarm_on();                 //sounds the alarm
        return presence;                  //returns UNAUTHORIZED
      }//endif
    }//endif
  }//endwhile
}//endfunction

void standby(){                           //only yellow LED on
  ptr = &red; ptr->init();                 //necessary for correcting red light bug
  ptr = &yellow; ptr->init();
  ptr->on();
  Serial.println("\nStanby mode on.");
  Serial.println("Aproximate tag/card to activate motion sensor alarm");
  Serial.println("or enter any character in the serial monitor to print log.");
  delay(1000);
  while(!reader.PICC_IsNewCardPresent()){   //waits for card/tag aproximation
    if (Serial.available()){
      log_list.printLog();
      while(Serial.available()) {     //clears serial entrys 
        if(Serial.read() == '\n') break; 
        Serial.read();
      }//endwhile
    }//endif
  }//endwhile
  ptr = &yellow; ptr->off();                //disables yellow LED
}

template<typename T>
void PIR<T>::alarm_on(){                //sounds the alarm
  while(!reader.PICC_IsNewCardPresent()){   //maintains loop while a card/tag isnt aproximated
    ptr = &yellow; ptr->on();
    ptr = &green; ptr->on();
    ptr = &red; ptr->on();
    ptr = &buzzer; ptr->on();

    delay(100);

    ptr = &yellow; ptr->off();
    ptr = &green; ptr->off();
    ptr = &red; ptr->off();
    ptr = &buzzer; ptr->off();
  }
  
  Serial.println("\nAlarm deactivated by card");
  Serial.println("Entering stanby mode...");
  delay(2000);
}
