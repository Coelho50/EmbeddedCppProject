

#ifndef RFID_HPP
#define RFID_HPP


#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>

class RFID{
  public:  
  RFID(byte, byte);
  ~RFID();

  void rfid_init(void);
  bool wait_for_card(void);
  bool read_card(void);

};



class User{
  public:
  //esse objeto 'chave' é utilizado para autenticação
    MFRC522::MIFARE_Key key;

  //código de status de retorno da autenticação
    MFRC522::StatusCode status; 

};


#endif