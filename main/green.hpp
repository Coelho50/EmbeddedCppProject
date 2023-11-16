
#ifndef GREEN_HPP
#define GREEN_HPP
#include "peripherals.hpp"

class Green: public Peripherals{
  public:
  void init();
  void on(void);
  void off(void);
};


#endif