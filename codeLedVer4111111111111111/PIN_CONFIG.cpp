#include "PIN_CONFIG.h"
void CLASS_CONFIG::FUNC_CONFIGPIN() {
  pinMode(led455 , OUTPUT);
  pinMode(led500 , OUTPUT);
  pinMode(led590 , OUTPUT);
  pinMode(led630 , OUTPUT);
  pinMode(led680 , OUTPUT);
  pinMode(led820 , OUTPUT);
  pinMode(led , OUTPUT);
  digitalWrite(led455 , 1);
  digitalWrite(led500 , 1);
  digitalWrite(led590 , 1);
  digitalWrite(led630 , 1);
  digitalWrite(led680 , 1);
  digitalWrite(led820 , 1);
  digitalWrite(led , 1);
  pinMode(en485 , OUTPUT);
  digitalWrite(en485, 0);
}
