

#ifndef RFID_HPP
#define RFID_HPP


#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>

class RFID: public MFRC522{  
  public:
    RFID(byte, byte);
    ~RFID(void);
/*
  void rfid_init(void);
  bool wait_for_card(void);
  bool read_card(void);
*/
};

#endif