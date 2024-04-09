#include "config_pin.h"
#include "main.h"
class_configpin configpin;
class_main mainRun;
uint32_t timeWaitLed = millis();
void setup() {
  configpin.Setup();
  mainRun.Setup();
  Serial.begin(9600);

}

void loop() {
 BlinkLed();

}

void BlinkLed() {
  uint8_t state13 = digitalRead(led);
  if (millis() - timeWaitLed > 1000) {
    digitalWrite(led, !state13);
    ui32_delayLed = millis();
  }
}
