#ifndef PIR_HPP
#define PIR_HPP

#include "peripherals.hpp"

typedef enum{
  AUTHORIZED = 0,
  UNAUTHORIZED
} PRESENCE;


class PIR{  
  public:
    Peripherals LEDS;
    byte digital_pin;

    PIR();
    ~PIR();
    bool pir_init(byte);
    PRESENCE motion_alarm();
};

#endif
