#ifndef I2C_TSL_h
#define I2C_TSL_h
#include "PIN_CONFIG.h"
class CLASS_I2CTSL {
  public:
    bool SETUP();
    void RUNNING(uint16_t &valus);
    void END();
};
#endif
