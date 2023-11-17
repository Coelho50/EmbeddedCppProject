//------------ includes ----------------

#include <SPI.h> //used for communication with RFID

#include <MFRC522.h>  //RFID library
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>

#include "PIR.hpp"   //classes made
#include "peripherals.hpp"

//------------ defines, global variables and objects --------------

#define SS_PIN 21 //setting SPI pins for RFID
#define RST_PIN 22

#define PIR_digital 4   //PIR sensor digital pin

#define pin_yellow  //LED and buzzer pin numbers
#define pin_green
#define pin_red
#define pin_buzzer

#define SIZE_BUFFER 18  //buffer size of each block in RFID card memory
#define MAX_SIZE_BLOCK 16 //number of memory blocks in RFID


MFRC522::MIFARE_Key key; //enable tag/card reading

MFRC522::StatusCode status; //gets the status for the read card/tag

MFRC522 reader(SS_PIN, RST_PIN); //declaring RFID and defining pins for SPI communication

PIR <byte> motion_sensor;


//--------------------- setup ------------------------------

void setup() {
  Serial.begin(115200);
  SPI.begin();  //communication with RFID

  reader.PCD_Init();  //initializes RFID

  delay(1000);

  Serial.println("\nSystem initialized");
  Serial.println("Entering standby, please aproximate tag to activate motion sensor alarm");

  
}

//--------------    LOOP     ---------------------------

void loop() {

  standby(); //Waits for card aproximation

  bool pir_activated = motion_sensor.pir_init(PIR_digital); //initializes PIR motion sensor

  if(!pir_activated){ //in case the motion sensor gets deactivated, the code returns to the start of the loop
    return;
  }//endif

  Serial.println("SYSTEM ACTIVATED");

  PRESENCE presence = motion_sensor.motion_alarm();
}  //endloop



