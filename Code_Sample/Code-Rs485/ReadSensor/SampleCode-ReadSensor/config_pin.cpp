#include "config_pin.h"
void class_confipin::Setup() {
  pinMode(En485, OUTPUT);
  pinMode(Led, OUTPUT);
  digitalWrite(En485,  HIGH);
  digitalWrite(Led,  HIGH);
  return;
}
