#ifndef SSRenke_h
#define SSRenke_h
#include <Arduino.h>
#include "SENSOR485.h"
class CLASS_SSR {
  private:
    uint16_t p_SSRrequestFrame[4] = {2, 3, 0, 6};
    uint16_t p_SSRespondFrame[6] = {0};
    float p_paraSSR = 0;
    float p_tempSSR = 0;
    bool (CLASS_SSR::*RunningFuncSSR)();
    bool Func_Read485SSR();
    bool Func_GetParaSSR();
    uint32_t Func_CombineHexSSR(uint16_t *hexArray);
    float Func_HexToFloatSSR(uint32_t hexData);
  public:
    void Func_SetupSSR();
    bool Func_RunningSSR(float *para, float *temp);
};
#endif
