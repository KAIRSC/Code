#include "SENSOR485.h"
#include <ModbusRtu.h>
#include <SoftwareSerial.h>
SoftwareSerial serial485(PC11, PC10);
Modbus master(0, serial485);
modbus_t registerSend;
void CLASS_SENSOR485::Setup485(uint16_t baudRate) {
  serial485.begin(9600);
  master.start();
  master.setTimeOut( 2000 ); // if there is no answer in 2000 ms, roll over

}
bool CLASS_SENSOR485::Running485( uint16_t *frame, uint8_t sizeofFrame, uint16_t *respondFrame, uint8_t sizeofrespondFrame) {
  uint8_t u8state = 0;
  unsigned long u32wait = millis() + 1000;
  uint16_t respondFrame1[sizeofrespondFrame] = {0};
  //  Serial.println("---------------------- ");
  //  Serial.println(sizeofrespondFrame);
  bool done = true;
  uint16_t timeout = 30000;
  unsigned long tTimeOut = millis();
  while (millis() -  tTimeOut < timeout) {
    switch ( u8state ) {
      case 0:
        if (millis() > u32wait) u8state++; // wait state
        break;
      case 1:
        registerSend.u8id = frame[0]; // slave address
        registerSend.u8fct = frame[1]; // function code (this one is registers read)
        registerSend.u16RegAdd = frame[2]; // start address in slave
        registerSend.u16CoilsNo = frame[3]; // number of elements (coils or registers) to read
        registerSend.au16reg = respondFrame1; // pointer to a memory array in the Arduino
        digitalWrite(en485, 1);
        master.query( registerSend); // send query (only once)
        u8state++;
        delay(5);
        break;
      case 2:
        digitalWrite(en485, 0);
        master.poll(); // check incoming messages
        if (master.getState() == COM_IDLE) {
          u8state = 0;
          u32wait = millis() + 10;
          for (int i = 0 ; i < sizeofrespondFrame ; i++) {
            respondFrame[i] = respondFrame1[i];
            Serial.print(respondFrame1[i], HEX); //Or do something else!
            Serial.print(" ");
          }
          Serial.println(" ");
          if (respondFrame1[0] != 0 || respondFrame1[1] != 0) {
            return 1;
          }
        }
        break;
    }
  }
  return 1;
}
bool CLASS_SENSOR485::Running485_2( uint8_t *frame, uint8_t sizeofFrame, uint8_t *respondFrame, uint8_t sizeofrespondFrame) {
  uint16_t timeout = 30000;
  unsigned long tTimeOut = millis();
  byte check = 0x0C;
  while (millis() -  tTimeOut < timeout) {
    digitalWrite(en485, 1);
    serial485.write(frame, sizeofFrame); // Gửi dữ liệu đi
    delay(5);
    digitalWrite(en485, 0);
    Serial.print("Response: ");
    for (int j = 0; j < 15; j++) {
      respondFrame[j] = serial485.read();
      Serial.print(respondFrame[j], HEX);
      Serial.print(" ");
    }
    Serial.println();
    if (respondFrame[0] == frame[0] && respondFrame[1] == frame[1]) {
      return 1;
    }
    Serial.println();
    delay(200);
  }
  return 1;
}
