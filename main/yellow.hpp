
#ifndef YELLOW_HPP
#define YELLOW_HPP
#include "peripherals.hpp"

class Yellow : public Peripherals{
  public:
  void init();
  void on(void);
  void off(void);
};


#endif