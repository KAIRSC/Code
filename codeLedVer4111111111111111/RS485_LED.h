#ifndef RS485_LED_h
#define RS485_LED_h
#include "PIN_CONFIG.h"


class CLASS_RS485LED {
  private:
    uint8_t posData = 0;
    uint8_t reagent = 0;
    uint16_t value;
    uint32_t timeWait = millis();
    bool error;
    bool varSendRead = true;
    uint8_t state = 0;
    uint8_t lengthReceive = 10;
    uint8_t bitRun = 114; //run: lay led pre
    uint8_t bitRun1 = 82; //Run: lay led later
    uint8_t bitData = 100;
    uint8_t bitError = 115;
    uint8_t bitCheck = 67;
    uint8_t mesSend[17] = {80, 87, 81, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}; //P-W-Q, cmd run || data ,led 1- led 6, end bs
    uint8_t mesReceive[10] ;     // P-W-Q, cmd run || data , reagent, drop, end bit
    uint8_t mesCompare[7];
    //float data = 0.0;
    bool READ_DATA();
    bool SEND_DATA();
    bool HANDLE_MES(uint8_t bitCheck);
    bool (CLASS_RS485LED::*P_MAIN)();
    //    bool READ_DATA(uint8_t type);
    //    bool SEND_DATA(uint8_t type);

  public:
    void SETUP();
    bool READ_CMDRUN(uint8_t &mode, uint8_t &reagent, uint8_t &drop);
    bool SEND_INFO_VALUE(float value);
    bool SEND_INFO_LED_PRE();
    bool SEND_ERROR();

};
#endif
