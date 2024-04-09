#include "SSRenke.h"
CLASS_SENSOR485 ssrSENSOR485;
void CLASS_SSR::Func_SetupSSR() {
  RunningFuncSSR = &CLASS_SSR::Func_Read485SSR;
}
bool CLASS_SSR::Func_RunningSSR(float *para, float *temp) {
  bool doneMain = (this ->*RunningFuncSSR)();
  if (doneMain) {
    *para = p_paraSSR;
    *temp = p_tempSSR;
  }
  return doneMain;
}
bool CLASS_SSR::Func_Read485SSR() {
  bool done = ssrSENSOR485.Func_Running485( p_SSRrequestFrame, sizeof(p_SSRrequestFrame), p_SSRespondFrame, sizeof(p_SSRespondFrame) / sizeof(uint16_t));
  if (done) {
    RunningFuncSSR = &CLASS_SSR::Func_GetParaSSR;
  }
  return 0;
}
bool CLASS_SSR::Func_GetParaSSR() {
  uint16_t hexParaArray[4] = {0};
  uint16_t  hexTempArray[4] = {0};
  for (uint8_t i = 0 ; i < 2 ; i++) {
    hexParaArray[i] = p_SSRespondFrame[2 + i];
    hexTempArray[i] = p_SSRespondFrame[4 + i];
  }
  uint32_t hexPara = Func_CombineHexSSR(hexParaArray);
  uint32_t hexTemp = Func_CombineHexSSR(hexTempArray);
  p_paraSSR = Func_HexToFloatSSR(hexPara);
  p_tempSSR = Func_HexToFloatSSR(hexTemp);
  RunningFuncSSR = &CLASS_SSR::Func_Read485SSR;
  return 1;
}
float CLASS_SSR::Func_HexToFloatSSR(uint32_t hexData) {
  uint8_t binary[32];
  int8_t bitSign = 1;
  int8_t bitBias = 0;
  float bitFloat = 0;
  float hexToFloat = 0 ;
  //Serial.print("Binary: ");
  for (uint8_t i = 0 ; i < 32 ; i++) {
    binary[31 - i] = (hexData >> i) & 0x01 ;

  }
  //  for (uint8_t i = 0 ; i < 32 ; i++) {
  //    Serial.print(binary[i]);
  //  }
  //  Serial.println("");
  bitSign = ((binary[0] == 0) ? 1 : (-1));
  //  Serial.print("bitSign: ");
  //  Serial.print( bitSign);
  //  Serial.println("");
  for (uint8_t i = 0 ; i < 8; i++) {
    bitBias += binary[i + 1] * pow(2, (7 - i));
  }
  bitBias -= 127;
  //  Serial.print("bitBias: ");
  //  Serial.print( bitBias);
  //  Serial.println("");
  for (uint8_t i = 0 ; i < 23; i++) {
    bitFloat += binary[i + 9] / pow(2,  i + 1);
  }
  //  Serial.print("bitFloat: ");
  //  Serial.print( bitFloat);
  //  Serial.println("");
  hexToFloat =  bitSign * (1 + bitFloat) * pow(2, bitBias);
  return hexToFloat;
}
uint32_t CLASS_SSR::Func_CombineHexSSR(uint16_t *hexArray) {
  uint32_t hexCombine = 0;
  hexCombine |= hexArray[0];
  hexCombine <<= 16;
  hexCombine |= hexArray[1];
  return hexCombine;
}
