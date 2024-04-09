#ifndef SSDODisen_h
#define SSDODisen_h
#include <Arduino.h>
#include "SENSOR485.h"
class CLASS_SSDODisen {
  private:
    uint8_t p_requestFrameSSDODisen[8] = {0x03, 0x03, 0x20, 0x0, 0x0, 0x6, 0xCF, 0xEA};
    uint8_t p_respondFrameSSDODisen[15] = {0};
    float p_paraSSDODisen = 0;
    float p_tempSSDODisen = 0;
    bool (CLASS_SSDODisen::*RunningFuncSSDODisen)();
    bool Func_Read485SSDODisen();
    bool Func_GetParaSSDODisen();
    uint32_t Func_CombineHexSSDODisen(uint8_t *hexArray);
    float Func_HexToFloatSSDODisen(uint32_t hexData);
  public:
    void Func_SetupSSDODisen();
    bool Func_RunningSSDODisen(float *para, float *temp);
};
#endif
