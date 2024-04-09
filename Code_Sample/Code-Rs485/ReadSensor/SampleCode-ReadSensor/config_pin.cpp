#include "config_pin.h"
void class_configpin::Setup() {
  pinMode(en485, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(en485,  HIGH);
  digitalWrite(led,  HIGH);
  return;
}
