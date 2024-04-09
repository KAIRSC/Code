#ifndef SENSOR485_h
#define SENSOR485_h
#include "config_pin.h"

class CLASS_SENSOR485 {
  private:

  public:
    void Setup485(uint16_t baudRate);
    bool Running485( uint16_t *frame, uint8_t sizeofFrame, uint16_t *respondFrame, uint8_t sizeofrespondFrame);
    bool Running485_2( uint8_t *frame, uint8_t sizeofFrame, uint8_t *respondFrame, uint8_t sizeofrespondFrame);
};
#endif
