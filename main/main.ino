//------------ includes ----------------

#include <SPI.h> 

#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>

#include "PIR.hpp"
#include "peripherals.hpp"

//------------ defines, global variables and objects --------------

#define SS_PIN 21
#define RST_PIN 22

#define PIR_digital 4

#define pin_yellow
#define pin_green
#define pin_red
#define pin_buzzer

#define SIZE_BUFFER 18
#define MAX_SIZE_BLOCK 16


MFRC522::MIFARE_Key key;

MFRC522::StatusCode status;

MFRC522 reader(SS_PIN, RST_PIN); //Defining pins for SPI communication

Peripherals peripherals;

//--------------------- setup ------------------------------

void setup() {
  Serial.begin(115200);
  SPI.begin();

  peripherals.peripherals_init();

  reader.PCD_Init();
  delay(1000);
  Serial.println("\n");
  Serial.println("\nSystem initialized");
  Serial.println("Entering standby, please aproximate tag to activate motion sensor alarm");
}

//--------------    LOOP     ---------------------------

void loop() {

  standby(); //Waits for card aproximation

  PIR motion_sensor;
  bool pir_activated = motion_sensor.pir_init(PIR_digital);

  if(!pir_activated){
    return;
  }//endif

  Serial.println("SYSTEM ACTIVATED");

  PRESENCE presence = motion_sensor.motion_alarm();
}  //endloop



