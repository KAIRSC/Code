#include "MACHINE_RUN.h"
#include <IWatchdog.h>
CLASS_MACHINERUN machine;
String inputString = "";
uint32_t timeLed = millis();
void setup() {
  IWatchdog.begin(15000000);
  Serial.begin(9600);
  machine.SETUP();
}
void loop() {
  machine.RUNNING();
//  if (inputString.indexOf("runcolor") >= 0) {
//    machine.ON_LED();
//    inputString = "";
//  }
  blinkLed();
}


void serialEvent() {
  inputString = "";
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar != '\n' && inChar != ' ' && inChar != '\r') {
      inputString += inChar;
    }
  }
  Serial.println(inputString);
}
void blinkLed() {
  uint8_t en = digitalRead(led);
  if (millis() - timeLed > 500) {
    IWatchdog.reload();
    digitalWrite(led, !en);
    timeLed = millis();
  }
}
