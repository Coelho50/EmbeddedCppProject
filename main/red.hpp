
#ifndef RED_HPP
#define RED_HPP
#include "peripherals.hpp"

class Red: public Peripherals{
  public:
  void init();
  void on(void);
  void off(void);
};


#endif