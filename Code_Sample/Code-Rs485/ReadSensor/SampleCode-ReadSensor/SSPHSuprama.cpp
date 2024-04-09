#include "SSPHSuprama.h"
CLASS_SENSOR485 ssPHSupramaSENSOR485;
void CLASS_SSPHSuprama::Func_SetupSSPHSuprama() {
  RunningFuncSSPHSuprama = &CLASS_SSPHSuprama::Func_Read485SSPHSuprama;
}
bool CLASS_SSPHSuprama::Func_RunningSSPHSuprama(float *para, float *temp) {
  bool doneMain = (this ->*RunningFuncSSPHSuprama)();
  if (doneMain) {
    *para = p_paraSSPHSuprama;
    *temp = p_tempSSPHSuprama;
  }
  return doneMain;
}
bool CLASS_SSPHSuprama::Func_Read485SSPHSuprama() {
  bool done = ssPHSupramaSENSOR485.Func_Running485(p_requestFrameSSPHSuprama, sizeof(p_requestFrameSSPHSuprama), p_respondFrameSSPHSuprama, sizeof(p_respondFrameSSPHSuprama) / sizeof(uint16_t));
  p_paraSSPHSuprama = 0;
  p_tempSSPHSuprama = 0;
  if (done) {
    RunningFuncSSPHSuprama = &CLASS_SSPHSuprama::Func_GetParaSSPHSuprama;
  }
  return 0;
}
bool CLASS_SSPHSuprama::Func_GetParaSSPHSuprama() {
  uint16_t hexPara = p_respondFrameSSPHSuprama[1];
  uint16_t hexTemp = p_respondFrameSSPHSuprama[0];
  p_paraSSPHSuprama = Func_HexToDecimalSSPHSuprama(hexPara) / 100;
  p_tempSSPHSuprama = Func_HexToDecimalSSPHSuprama(hexTemp) / 10;
  RunningFuncSSPHSuprama = &CLASS_SSPHSuprama::Func_Read485SSPHSuprama;
  return 1;
}
float CLASS_SSPHSuprama::Func_HexToDecimalSSPHSuprama(uint16_t hexData) {
  float hexDecimal = 0;
  char hexArray[5];
  sprintf(hexArray, "%04X", hexData);
  uint16_t hexInt = (uint16_t)strtol(hexArray, NULL, 16);
  hexDecimal = hexInt / 1.0;
  return hexDecimal;
}
//uint16_t CLASS_SSPHSuprama::Func_CombineHexSSPHSuprama(uint8_t *hexArray) {
//  Serial.println("Combine Decimal");
//  uint16_t hexCombine = 0;
//  hexCombine |= hexArray[0];
//  hexCombine <<= 8;
//  hexCombine |= hexArray[1];
//  hexCombine <<= 8;
//  return hexCombine;
//}
