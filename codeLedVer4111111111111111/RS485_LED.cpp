#include "RS485_LED.h"
#define RS485Serial Serial1
void CLASS_RS485LED::SETUP() {
  RS485Serial.begin(9600);
  digitalWrite(en485, 0);
  return;
}
bool CLASS_RS485LED::READ_CMDRUN(uint8_t &mode, uint8_t &reagent, uint8_t &drop) {
  bool done = false;
  if (varSendRead) {
    if (READ_DATA()) {
      if (HANDLE_MES(bitRun) || HANDLE_MES(bitRun1)) {
        varSendRead = false;
        if (HANDLE_MES(bitRun)) {
          mode = bitRun;
          reagent = mesCompare[4];
          drop = mesCompare[5];
          mesSend[3] = bitRun;
        }
        if (HANDLE_MES(bitRun1)) {
          mode = bitRun1;
          mesSend[3] = bitRun1;
        }
        SEND_DATA();
        done = true;
        return 1;
      }
    }
  }
  return 0;

}
bool CLASS_RS485LED::SEND_INFO_VALUE(float value) {
  bool done = false;
  if (!varSendRead) {
    mesSend[3] = bitData;
    //Serial.print("data send: ");
    //    for (uint8_t i = 4 ; i < 6; i++) {
    value = value * 100;
    mesSend[4]  = value  / 10000;
    mesSend[5] = (value - (mesSend[4] * 10000)) / 100;
    mesSend[6]  = value - (mesSend[4] * 10000) - (mesSend[5] * 100);
    Serial.println( String(value) + " " + String(mesSend[4]) + " " + String(mesSend[5]) + " " + String(mesSend[6]));
    //      Serial.print(" ");
    // }
    //Serial.println(" ");
    SEND_DATA();
    varSendRead = true;
    timeWait = millis();
  } else if (varSendRead) {
    if (millis() - timeWait >= 5001) {
      error = 1;
      done = true;
    }
    else if (READ_DATA()) {
      if (HANDLE_MES(bitData))
        done = true;
    }
  }
  return done;
}
bool CLASS_RS485LED::SEND_INFO_LED_PRE() {
  bool done = false;
  if (!varSendRead) {
    mesSend[3] = bitRun1;
    SEND_DATA();
    varSendRead = true;
    timeWait = millis();
  } else if (varSendRead) {
    if (millis() - timeWait >= 5000) {
      error = 1;
      done = true;
    }
    else if (READ_DATA()) {
      if (HANDLE_MES(bitRun1))
        done = true;
    }
  }
  return done;
}
bool CLASS_RS485LED::SEND_ERROR() {
  bool done = false;
  if (!varSendRead) {
    mesSend[3] = bitError;
    SEND_DATA();
    varSendRead = true;
    timeWait = millis();
  } else if (varSendRead) {
    if (millis() - timeWait >= 2000) {
      error = 1;
      done = true;
    }
    else if (READ_DATA()) {
      if (HANDLE_MES(bitError))
        done = true;
    }
  }
  return done;
}
bool CLASS_RS485LED::READ_DATA() {
  if (RS485Serial.available()) {
    RS485Serial.readBytes(mesReceive, lengthReceive);
    for (int i = 0; i < lengthReceive; i++) {
      if (mesReceive[i] == mesSend[0]) {
        for (uint8_t j = 0 ; j < 7   ; j++) {
          mesCompare[j] = mesReceive[i + j];
          Serial.print(mesCompare[j]);
          Serial.print(" ");
        }
        break;
      }
    }
    Serial.println(" ");
    if (mesCompare[0] == mesSend[0] && mesCompare[1] == mesSend[1] && mesCompare[2] == mesSend[2] && mesCompare[6] == mesSend[16])
    {
      return true;
    }
  }
  return false;
}
bool CLASS_RS485LED::SEND_DATA() {
  delay(20);
  digitalWrite(en485, HIGH);
  RS485Serial.write(mesSend, sizeof(mesSend));
  delay(30);
  digitalWrite(en485, LOW);
  return 0;
}
bool CLASS_RS485LED::HANDLE_MES(uint8_t bitCheck) {
  if (mesCompare[3] ==  bitCheck)
    return 1;
  return 0;
}
