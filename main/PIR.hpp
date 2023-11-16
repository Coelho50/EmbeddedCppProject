#ifndef PIR_HPP
#define PIR_HPP

#include "peripherals.hpp"

typedef enum{
  AUTHORIZED = 0,
  UNAUTHORIZED
} PRESENCE;

template<typename T>
class PIR{  
  public:
    Peripherals LEDS;
    T digital_pin;

    PIR();
    ~PIR();
    bool pir_init(T);
    PRESENCE motion_alarm();
};

#endif
