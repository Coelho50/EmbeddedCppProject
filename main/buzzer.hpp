
#ifndef BUZZER_HPP
#define BUZZER_HPP
#include "peripherals.hpp"
#include <Arduino.h>

class Buzzer: public Peripherals{
  public:
  void init();
  void on(void);
  void off(void);
};


#endif