#include "SSDOY505.h"
CLASS_SENSOR485 SSDOY505SENSOR485;
void CLASS_SSDOY505::Func_SetupSSDOY505() {
  RunningFuncSSDOY505 = &CLASS_SSDOY505::Func_Read485SSDOY505;
}
bool CLASS_SSDOY505::Func_RunningSSDOY505(float *para, float *temp) {
  bool doneMain = (this ->*RunningFuncSSDOY505)();
  if (doneMain) {
    *para = p_paraSSDOY505;
    *temp = p_tempSSDOY505;
  }
  return doneMain;
}
bool CLASS_SSDOY505::Func_Read485SSDOY505() {
  bool done = SSDOY505SENSOR485.Func_Running485_2(p_requestFrameSSDOY505, sizeof(p_requestFrameSSDOY505), p_respondFrameSSDOY505, sizeof(p_respondFrameSSDOY505) / sizeof(uint16_t));
  p_paraSSDOY505 = 0;
  p_tempSSDOY505 = 0;
  if (done) {
    RunningFuncSSDOY505 = &CLASS_SSDOY505::Func_GetParaSSDOY505;
  }
  return 0;
}
bool CLASS_SSDOY505::Func_GetParaSSDOY505() {
  uint8_t hexParaArray[4] = {0};
  uint8_t  hexTempArray[4] = {0};
  for (uint8_t i = 0 ; i < 4 ; i++) {
    hexParaArray[i] = p_respondFrameSSDOY505[14 - i];
    hexTempArray[i] = p_respondFrameSSDOY505[6 - i];
  }
  uint32_t hexPara = Func_CombineHexSSDOY505(hexParaArray);
  uint32_t hexTemp = Func_CombineHexSSDOY505(hexTempArray);
  p_paraSSDOY505 = Func_HexToFloatSSDOY505(hexPara);
  p_tempSSDOY505 = Func_HexToFloatSSDOY505(hexTemp);
  RunningFuncSSDOY505 = &CLASS_SSDOY505::Func_Read485SSDOY505;
  return 1;
}
float CLASS_SSDOY505::Func_HexToFloatSSDOY505(uint32_t hexData) {
  uint8_t binary[32];
  int8_t bitSign = 1;
  int8_t bitBias = 0;
  float bitFloat = 0;
  float hexToFloat = 0 ;
  for (uint8_t i = 0 ; i < 32 ; i++) {
    binary[31 - i] = (hexData >> i) & 0x01 ;
  }
  bitSign = ((binary[0] == 0) ? 1 : (-1));
  for (uint8_t i = 0 ; i < 8; i++) {
    bitBias += binary[i + 1] * pow(2, (7 - i));
  }
  bitBias -= 127;
  for (uint8_t i = 0 ; i < 23; i++) {
    bitFloat += binary[i + 9] / pow(2,  i + 1);
  }
  hexToFloat =  bitSign * (1 + bitFloat) * pow(2, bitBias);
  return hexToFloat;
}
uint32_t CLASS_SSDOY505::Func_CombineHexSSDOY505(uint8_t *hexArray) {
  uint32_t hexCombine = 0;
  hexCombine |= hexArray[0];
  hexCombine <<= 8;
  hexCombine |= hexArray[1];
  hexCombine <<= 8;
  hexCombine |= hexArray[2];
  hexCombine <<= 8;
  hexCombine |= hexArray[3];
  // hexCombine = (hexArray[1] << 16 | hexArray[0]) ;
  //  hexCombine <<= 16;
  //  hexCombine |= hexArray[1];
  //      hex = (arr[1] << 16) | arr[0];
  Serial.println(hexCombine,HEX);
  return hexCombine;
}
