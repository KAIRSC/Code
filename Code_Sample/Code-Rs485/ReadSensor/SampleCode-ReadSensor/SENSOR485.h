#ifndef SENSOR485_h
#define SENSOR485_h
#include "CONFIGPIN.h"

class CLASS_SENSOR485 {
  private:

  public:
    void Func_Setup485(uint16_t baudRate);
    bool Func_Running485( uint16_t *frame, uint8_t sizeofFrame, uint16_t *respondFrame, uint8_t sizeofrespondFrame);
    bool Func_Running485_2( uint8_t *frame, uint8_t sizeofFrame, uint8_t *respondFrame, uint8_t sizeofrespondFrame);
};
#endif
