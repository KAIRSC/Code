#ifndef SSSalinityDaxi_h
#define SSSalinityDaxi_h
#include <Arduino.h>
#include "SENSOR485.h"
class CLASS_SSSalinityDaxi {
  private:
    uint16_t p_requestFrameSSSalinityDaxi[4] = {4, 3, 0, 4};
    uint16_t p_respondFrameSSSalinityDaxi[4] = {0};
    float p_paraSSSalinityDaxi = 0;
    float p_tempSSSalinityDaxi = 0;
    bool (CLASS_SSSalinityDaxi::*RunningFuncSSSalinityDaxi)();
    bool Read485SSSalinityDaxi();
    bool GetParaSSSalinityDaxi();
    //uint16_t CombineHexSSSalinityDaxi(uint16_t *hexArray);
    float HexToDecimalSSSalinityDaxi(uint16_t hexData);
  public:
    void SetupSSSalinityDaxi();
    bool RunningSSSalinityDaxi(float &para, float &temp);
};
#endif
