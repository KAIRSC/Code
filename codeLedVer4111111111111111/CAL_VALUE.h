#ifndef CAL_VALUE_h
#define CAL_VALUE_h
#include "PIN_CONFIG.h"
class CLASS_CALVALUE {
  private:
    float CAL_PH(uint16_t ledBefore[], uint16_t ledAfter[]);
    float CAL_NH3(uint16_t ledBefore[], uint16_t ledAfter[]);
    float CAL_NO2(uint16_t ledBefore[], uint16_t ledAfter[]);
    float CAL_KH(uint16_t ledBefore[], uint16_t ledAfter[], uint8_t drop);
    float CAL_MG(uint16_t ledBefore[], uint16_t ledAfter[], uint8_t drop);
    float CAL_CA(uint16_t ledBefore[], uint16_t ledAfter[], uint8_t drop);
    float CAL_METHODPH(float* X, float* coffs,float inter, uint8_t num);
    float CAL_METHOD0(uint16_t* ledBefore, uint16_t* ledAfter, float*coffs, float inter, uint8_t num);
    float CAL_METHOD1(uint16_t* ledBefore, uint16_t* ledAfter, uint8_t num);
  public:
    bool FIND_PARAM(float &valu, uint16_t ledBefore[], uint16_t ledAfter[], uint8_t reagent, uint8_t drop);

};

#endif
