#include "PIR.hpp"

PIR::PIR(){}

PIR::~PIR(){}


bool PIR::pir_init(byte digital_pin){
  bool confirmation = false;

  Serial.println("\nActivating alarm in 120 seconds");
  Serial.println("To cancel this action, hold your tag in front of the reader for 1 full second.\n");

  delay(500);

  int i = 120; 
  //for loop not working?

  while (i>0){   //-----> PRINT REMAINING TIME
    i--;

    if (i%10 == 0){
    Serial.println(String("Seconds remaining: ") + i);
    }//endif

    delay(1000);    //-----------> DEACTIVATE FOR TESTING

    if (reader.PICC_IsNewCardPresent()){
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

}//endfunction