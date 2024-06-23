#include "MACHINE_RUN.h"
#include "CAL_VALUE.h"
CLASS_I2CTSL i2c_tsl;
CLASS_CONFIG configPin;
CLASS_RS485LED rs485;
CLASS_CALVALUE calulate;
void CLASS_MACHINERUN::ON_LED() {
  Serial.println("run ne");
  if (i2c_tsl.SETUP()) {
    Serial.println("do chat ss: " + String(reagent));
    uint8_t soLed = 6;
    uint16_t value[soLed] = {0};
    //    for (uint8_t i = 0 ; i < 2 ; i++) {ss
    digitalWrite(led455 , 0);
    i2c_tsl.RUNNING(value[0]);
    //value[0] = kalmanFilter0.updateEstimate(value[0]);
    digitalWrite(led455 , 1);
    delay(200);
    digitalWrite(led500 , 0);
    i2c_tsl.RUNNING(value[1]);
    //value[1] = kalmanFilter1.updateEstimate(value[1]);
    digitalWrite(led500 , 1);
    delay(200);
    digitalWrite(led590 , 0);
    i2c_tsl.RUNNING(value[2]);
    //value[2] = kalmanFilter2.updateEstimate(value[2]);
    digitalWrite(led590 , 1);
    delay(200);
    digitalWrite(led630 , 0);
    i2c_tsl.RUNNING(value[3]);
    // value[3] = kalmanFilter3.updateEstimate(value[3]);
    digitalWrite(led630 , 1);
    delay(200);
    digitalWrite(led680 , 0);
    i2c_tsl.RUNNING(value[4]);
    //value[4] = kalmanFilter4.updateEstimate(value[4]);
    digitalWrite(led680 , 1);
    delay(200);
    digitalWrite(led820 , 0);
    i2c_tsl.RUNNING(value[5]);
    //value[5] = kalmanFilter5.updateEstimate(value[5]);
    digitalWrite(led820 , 1);
    delay(200);
    //    }
    for (uint8_t i = 0 ; i < 6; i++) {
      Serial.println("gia tri led thu: " + String(i + 1) + " la: " + String(value[i]));
    }
  }
  delay(1000);
  return;
}
void CLASS_MACHINERUN::SETUP() {
  configPin.FUNC_CONFIGPIN();
  rs485.SETUP();
  P_RUNNING = &CLASS_MACHINERUN::Rs485_WAITING;
}
void CLASS_MACHINERUN::CONVERT_NUM_TO_BYTE(uint16_t *num, uint8_t lengthNum) {
  uint8_t orderData = 0;
  for (uint8_t k = 0 ; k < lengthNum ; k++) {
    uint8_t type = 16;
    uint8_t divType = 8;
    uint8_t binary[type] = {0};
    for (uint8_t j = 0; j < type ; j++) {
      if (num[k] & (1 << j))
        binary[j] = 1;
      else
        binary[j] = 0;
    }
    for (uint8_t i = 0 ; i <  divType ; i++) {
      dataLed[orderData] += binary[i] * pow(2, i);
    }
    for (uint8_t i = divType ; i <  type ; i++) {
      dataLed[orderData + 1] += binary[i] * pow(2, i - divType);
    }
    orderData += 2;
  }
  return;
}
bool CLASS_MACHINERUN::Rs485_WAITING() {
  if (rs485.READ_CMDRUN(mode, reagent, drop))
    P_RUNNING = &CLASS_MACHINERUN::I2CTSL;
  return 0;
}
bool CLASS_MACHINERUN::I2CTSL() {
  if (i2c_tsl.SETUP()) {
    digitalWrite(led455 , 0);
    i2c_tsl.RUNNING(dataLed[0]);
    digitalWrite(led455 , 1);
    delay(200);
    digitalWrite(led500 , 0);
    i2c_tsl.RUNNING(dataLed[1]);
    digitalWrite(led500 , 1);
    delay(200);
    digitalWrite(led590 , 0);
    i2c_tsl.RUNNING(dataLed[2]);
    digitalWrite(led590 , 1);
    delay(200);
    digitalWrite(led630 , 0);
    i2c_tsl.RUNNING(dataLed[3]);
    digitalWrite(led630 , 1);
    delay(200);
    digitalWrite(led680 , 0);
    i2c_tsl.RUNNING(dataLed[4]);
    digitalWrite(led680 , 1);
    delay(200);
    digitalWrite(led820 , 0);
    i2c_tsl.RUNNING(dataLed[5]);
    digitalWrite(led820 , 1);
    delay(200);
    for (uint8_t i = 0 ; i < 6; i++) {
      Serial.println("gia tri led thu: " + String(i + 1) + " la: " + String(dataLed[i]));
    }
    P_RUNNING = &CLASS_MACHINERUN::Rs485_SEND_DATA;
    return 0;
  }
  else
    P_RUNNING = &CLASS_MACHINERUN::Rs485_SEND_ERROR;

  return 0;
}
bool CLASS_MACHINERUN::Rs485_SEND_DATA() {
  bool done = 0;
  if (mode == 114) {
    float value = 0.0;
    calulate.FIND_PARAM(value, led_pre, dataLed, reagent, drop);
    while (!rs485.SEND_INFO_VALUE(value));
    done = 1;

  }
  else if (mode == 82) {
    memset(led_pre, 0 , sizeof(led_pre));
    memcpy(led_pre, dataLed, sizeof(led_pre));
    while (!rs485.SEND_INFO_LED_PRE());
    done = 1;

  }
  if (done)
    P_RUNNING = &CLASS_MACHINERUN::Rs485_WAITING;
  return 0;
}

bool CLASS_MACHINERUN::Rs485_SEND_ERROR() {
  if (rs485.SEND_ERROR()) {
    P_RUNNING = &CLASS_MACHINERUN::Rs485_WAITING;
    return 1;
  }
  return 0;
}

void CLASS_MACHINERUN::RUNNING() {
  bool done = (this->*P_RUNNING)();
  return;
}
