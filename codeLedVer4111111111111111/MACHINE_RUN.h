#ifndef MACHINE_RUN_h
#define MACHINE_RUN_h
#include "PIN_CONFIG.h"
#include "I2C_TSL.h"
#include "RS485_LED.h"
class CLASS_MACHINERUN {
  private:
    uint8_t mode = 0;
    uint8_t reagent;
    uint8_t drop;
    uint16_t dataLed[6] = {0};
    uint16_t led_pre[6] = {0};
    bool (CLASS_MACHINERUN::*P_RUNNING)();
    bool Rs485_WAITING();
    bool Rs485_SEND_DATA();
    bool Rs485_SEND_ERROR();
    bool I2CTSL();
    void CONVERT_NUM_TO_BYTE(uint16_t *nus, uint8_t lengthNum);
  public:
    void ON_LED();
    void SETUP();
    void RUNNING();
};
#endif
