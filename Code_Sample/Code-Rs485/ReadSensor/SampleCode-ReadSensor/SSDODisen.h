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
    bool Read485SSDODisen();
    bool GetParaSSDODisen();
    uint32_t CombineHexSSDODisen(uint8_t *hexArray);
    float HexToFloatSSDODisen(uint32_t hexData);
  public:
    void SetupSSDODisen();
    bool RunningSSDODisen(float &para, float &temp);
};
#endif
