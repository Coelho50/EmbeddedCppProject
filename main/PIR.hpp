#ifndef PIR_HPP
#define PIR_HPP

#include "yellow.hpp"
#include "green.hpp"
#include "red.hpp"
#include "buzzer.hpp"

typedef enum{
  AUTHORIZED = 0,
  UNAUTHORIZED
} PRESENCE;

template<typename T> //template used for specification purposes
class PIR{  //presence/motion sensor's class
  public:

    T digital_pin;   //sensor's output/digital pin

    bool pir_init(T);
    PRESENCE motion_alarm();
    friend void standby(void);
    void alarm_on();
};

#endif
