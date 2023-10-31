#include "RFID.hpp"

RFID::RFID(byte SS, byte RS){
  MFRC522 leitor(SS, RS);
}

void RFID::rfid_init(){
  mfrc522.PCD_Init(); 
}

bool RFID::wait_for_card(){
  bool  card = leitor.PICC_IsNewCardPresent();
  return card;
}

bool RFID::read_card(){
  bool card = leitor.PICC_ReadCardSerial();
  return card;
}