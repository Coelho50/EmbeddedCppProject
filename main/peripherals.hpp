
//#define yellow 33
//#define green  32 
//#define red    14 
//#define buzzer 12


#ifndef PERIPHERALS_HPP
#define PERIPHERALS_HPP

#include <string>
#include <Arduino.h>

class Peripherals{    //virtual base class to be inherited by all peripherals
  public:
    virtual void init();
    virtual void on(void);
    virtual void off(void);
};


#endif