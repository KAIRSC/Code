#ifndef config_pin_h
#define config_pin_h
#include <Arduino.h>
#define en485 PA15
#define led PC13

#define CF_Pump Q1
class class_configpin {
  public:
    void Setup();
};
#endif
