#ifndef SSPHSuprama_h
#define SSPHSuprama_h
#include <Arduino.h>
#include "SENSOR485.h"
class CLASS_SSPHSuprama {
  private:
    uint16_t p_requestFrameSSPHSuprama[4] = {1, 3, 0, 3};
    uint16_t p_respondFrameSSPHSuprama[2] = {0};
    float p_paraSSPHSuprama = 0;
    float p_tempSSPHSuprama = 0;
    bool (CLASS_SSPHSuprama::*RunningFuncSSPHSuprama)();
    bool Func_Read485SSPHSuprama();
    bool Func_GetParaSSPHSuprama();
    uint16_t Func_CombineHexSSPHSuprama(uint8_t *hexArray);
    float Func_HexToDecimalSSPHSuprama(uint16_t hexData);
  public:
    void Func_SetupSSPHSuprama();
    bool Func_RunningSSPHSuprama(float *para, float *temp);
};
#endif
