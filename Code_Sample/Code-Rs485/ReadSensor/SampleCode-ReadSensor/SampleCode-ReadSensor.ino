#include "config_pin.h"
#include "main.h"
class_configpin configpin;
class_main main;
void setup() {
  configpin.Setup();
  main.Setup();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}
