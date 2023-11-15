
#ifndef PERIPHERALS_HPP
#define PERIPHERALS_HPP



class Peripherals{
  public:
    //Peripherals(void);
    //~Peripherals(void);
    void peripherals_init(void);
    friend void standby(void);
    void activate_green(void);
    void deactivate_green(void);
    void aborted_activation(void);
    void alarm_on(void);
};


#endif