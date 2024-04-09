#ifndef SSPHHonde_h
#define SSPHHonde_h
#include <Arduino.h>
#include "SENSOR485.h"
class CLASS_SSPHHonde {
  private:
    uint16_t p_requestFrameSSPHHonde[4] = {6, 3, 0, 1};
    uint16_t p_respondFrameSSPHHonde[2] = {0};
    float p_paraSSPHHonde = 0;
    float p_tempSSPHHonde = 0;
    bool (CLASS_SSPHHonde::*RunningFuncSSPHHonde)();
    bool Read485SSPHHonde();
    bool GetParaSSPHHonde();
    uint16_t CombineHexSSPHHonde(uint8_t *hexArray);
    float HexToDecimalSSPHHonde(uint16_t hexData);
  public:
    void SetupSSPHHonde();
    bool RunningSSPHHonde(float &para, float &temp);
};
#endif
