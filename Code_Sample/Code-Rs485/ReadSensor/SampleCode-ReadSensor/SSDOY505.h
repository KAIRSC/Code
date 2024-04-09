#ifndef SSDOY505_h
#define SSDOY505_h
#include <Arduino.h>
#include "SENSOR485.h"
class CLASS_SSDOY505 {
  private:
    uint8_t p_requestFrameSSDOY505[8] = {0x05, 0x03, 0x26, 0x0, 0x0, 0x6, 0xCF, 0x04};
    uint8_t p_respondFrameSSDOY505[15] = {0};
    float p_paraSSDOY505 = 0;
    float p_tempSSDOY505 = 0;
    bool (CLASS_SSDOY505::*RunningFuncSSDOY505)();
    bool Func_Read485SSDOY505();
    bool Func_GetParaSSDOY505();
    uint32_t Func_CombineHexSSDOY505(uint8_t *hexArray);
    float Func_HexToFloatSSDOY505(uint32_t hexData);
  public:
    void Func_SetupSSDOY505();
    bool Func_RunningSSDOY505(float *para, float *temp);
};
#endif
