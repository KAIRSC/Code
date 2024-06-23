#ifndef PIN_CONFIG_h
#define PIN_CONFIG_h
#include <Arduino.h>
#define led455  PA0
#define led500  PA1
#define led590  PA2
#define led630  PA3
#define led680  PA4
#define led820  PA5
#define led  PC13
#define en485    PA8
#define tx485     PA9
#define rx485     PA10
class CLASS_CONFIG {
  public:
    void FUNC_CONFIGPIN();
};
#endif
