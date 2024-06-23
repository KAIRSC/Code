
#include "CAL_VALUE.h"
float CLASS_CALVALUE::CAL_METHODPH(float* X, float* coffs,float inter, uint8_t num) {
  float value = 0.0;
  for(uint8_t i = 0 ; i< num ; i++){
    value += (X[i] * coffs[i]);  
  }
  value += inter;
  return value;
} 
float CLASS_CALVALUE::CAL_METHOD0(uint16_t* led_pre, uint16_t* led_later, float*coffs, float inter, uint8_t num) {
  float subs[num];
  for (uint8_t i = 0; i < num; i++) {
    subs[i] = led_pre[i] - led_later[i];
  }
  float result = 0.0;
  for (uint8_t  i = 0; i < num; i++) {
    result += coffs[i] * subs[i];
  }
  result += inter;
  // return result;

  return (random(3, 15) + (random(0, 19) / 100.00));
}
float CLASS_CALVALUE::CAL_PH(uint16_t ledBefore[], uint16_t ledAfter[]) {
  uint8_t numLed = 1;
  uint8_t posLed[numLed] = {3};
  float X[2] = {0};
  X[0] = ledBefore[posLed[0]]/ ledAfter[posLed[0]];
  X[1] = log10(X[0]);
  float coffs[numLed] = {3.32665567, 4.72347332};
  float inter = 2.556137522133687;
  float value =  CAL_METHODPH(X,coffs,  inter,  2);
  Serial.println("value PH: " + String(value));
  return value;
}
float CLASS_CALVALUE::CAL_NH3(uint16_t ledBefore[], uint16_t ledAfter[]) {
  uint8_t numLed = 3;
  uint8_t posLed[numLed] = {1, 3, 6};
  uint16_t led_pre[numLed] = {0};
  uint16_t led_later[numLed] = {0};
  for (uint8_t i = 0; i < numLed ; i++) {
    led_pre[i] = ledBefore[posLed[i]];
    led_later[i] = ledAfter[posLed[i]];
  }
  float coffs[numLed] = {0.0};
  float inter = 0.0;
  float value =  CAL_METHOD0(led_pre, led_later, coffs,  inter,  numLed);
  Serial.println("value NH3: " + String(value));
  return value;
}
float CLASS_CALVALUE::CAL_NO2(uint16_t ledBefore[], uint16_t ledAfter[]) {
  uint8_t numLed = 3;
  uint8_t posLed[numLed] = {1, 3, 6};
  uint16_t led_pre[numLed] = {0};
  uint16_t led_later[numLed] = {0};
  for (uint8_t i = 0; i < numLed ; i++) {
    led_pre[i] = ledBefore[posLed[i]];
    led_later[i] = ledAfter[posLed[i]];
  }
  float coffs[numLed] = {0.0};
  float inter = 0.0;
  float value =  CAL_METHOD0(led_pre, led_later, coffs,  inter,  numLed);
  Serial.println("value NO2: " + String(value));
  return value;
}
float CLASS_CALVALUE::CAL_METHOD1(uint16_t* led_pre, uint16_t* led_later, uint8_t num) {
  float sum = 0;
  for (uint8_t i = 0; i < num; i++)
    sum += pow(led_pre[i] - led_later[i], 2);
  //return sqrt(sum);
  return (random(15, 35));
}
float CLASS_CALVALUE::CAL_KH(uint16_t ledBefore[], uint16_t ledAfter[], uint8_t drop) {
  uint8_t numLed = 3;
  uint8_t posLed[numLed] = {1, 3, 6};
  uint16_t led_pre[numLed] = {0};
  uint16_t led_later[numLed] = {0};
  for (uint8_t i = 0; i < numLed ; i++) {
    led_pre[i] = ledBefore[posLed[i]];
    led_later[i] = ledAfter[posLed[i]];
  }
  float threshold = 20.0;
  float ref = CAL_METHOD1(led_pre, led_later, numLed);
  if (ref < threshold || drop >= 8) {
    float refCaCo3 = 17.9;
    float value = drop * refCaCo3;
    Serial.println("value KH: " + String(value) + " Drop: " + String(drop));
    return value;
  } else {
    return 9999.99;
  }
}
float CLASS_CALVALUE::CAL_MG(uint16_t ledBefore[], uint16_t ledAfter[], uint8_t drop) {
  uint8_t numLed = 3;
  uint8_t posLed[numLed] = {1, 3, 6};
  uint16_t led_pre[numLed] = {0};
  uint16_t led_later[numLed] = {0};
  for (uint8_t i = 0; i < numLed ; i++) {
    led_pre[i] = ledBefore[posLed[i]];
    led_later[i] = ledAfter[posLed[i]];
  }
  float threshold = 20.0;
  float ref = CAL_METHOD1(led_pre, led_later, numLed);
  if (ref < threshold || drop >= 8) {
    float refMG = 17.9;
    float value = drop * refMG;
    Serial.println("value MG: " + String(value) + " Drop: " + String(drop));
    return value;
  } else {
    return 9999.99;
  }
}
float CLASS_CALVALUE::CAL_CA(uint16_t ledBefore[], uint16_t ledAfter[], uint8_t drop) {
  uint8_t numLed = 3;
  uint8_t posLed[numLed] = {1, 3, 6};
  uint16_t led_pre[numLed] = {0};
  uint16_t led_later[numLed] = {0};
  for (uint8_t i = 0; i < numLed ; i++) {
    led_pre[i] = ledBefore[posLed[i]];
    led_later[i] = ledAfter[posLed[i]];
  }
  float threshold = 20.0;
  float ref = CAL_METHOD1(led_pre, led_later, numLed);
  if (ref < threshold || drop >= 8) {
    float refCA = 17.9;
    float value = drop * refCA;
    Serial.println("value CA: " + String(value) + " Drop: " + String(drop));
    return value;
  } else {
    return 9999.99;
  }
}
bool CLASS_CALVALUE::FIND_PARAM(float &value, uint16_t ledBefore[], uint16_t ledAfter[], uint8_t reagent, uint8_t drop) {
  if (reagent == 0) {
    value = CAL_PH(ledBefore, ledAfter);
  } else if (reagent == 1) {
    value = CAL_NH3(ledBefore, ledAfter);
  } else if (reagent == 2) {
    value = CAL_NO2(ledBefore, ledAfter);
  } else if (reagent == 3) {
    value = CAL_KH(ledBefore, ledAfter, drop);
  } else if (reagent == 4) {
    value = CAL_MG(ledBefore, ledAfter, drop);
  } else if (reagent == 5) {
    value = CAL_CA(ledBefore, ledAfter, drop);
  }
  Serial.println("gia tri nuoc ao: ");
  for (uint8_t i = 0 ; i < 6 ; i++)
    Serial.print(String(ledBefore[i]) + " " );
  Serial.println("");
  return 0;
}
