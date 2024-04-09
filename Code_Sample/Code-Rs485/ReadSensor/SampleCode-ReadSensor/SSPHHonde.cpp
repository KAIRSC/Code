#include "SSPHHonde.h"
CLASS_SENSOR485 SSPHHondeSENSOR485;
void CLASS_SSPHHonde::SetupSSPHHonde() {
  RunningFuncSSPHHonde = &CLASS_SSPHHonde::Read485SSPHHonde;
}
bool CLASS_SSPHHonde::RunningSSPHHonde(float &para, float &temp) {
  bool doneMain = (this ->*RunningFuncSSPHHonde)();
  if (doneMain) {
     para = p_paraSSPHHonde;
     temp = p_tempSSPHHonde;
  }
  return doneMain;
}
bool CLASS_SSPHHonde::Read485SSPHHonde() {
  bool done = SSPHHondeSENSOR485.Running485(p_requestFrameSSPHHonde, sizeof(p_requestFrameSSPHHonde), p_respondFrameSSPHHonde, sizeof(p_respondFrameSSPHHonde) / sizeof(uint16_t));
  p_paraSSPHHonde = 0;
  p_tempSSPHHonde = 0;
  if (done) {
    RunningFuncSSPHHonde = &CLASS_SSPHHonde::GetParaSSPHHonde;
  }
  return 0;
}
bool CLASS_SSPHHonde::GetParaSSPHHonde() {
  uint16_t hexPara = p_respondFrameSSPHHonde[0];
  //uint16_t hexTemp = p_respondFrameSSPHHonde[0];
  p_paraSSPHHonde = HexToDecimalSSPHHonde(hexPara) / 100;
  //p_tempSSPHHonde = HexToDecimalSSPHHonde(hexTemp) / 10;
  p_tempSSPHHonde = 0;
  RunningFuncSSPHHonde = &CLASS_SSPHHonde::Read485SSPHHonde;
  return 1;
}
float CLASS_SSPHHonde::HexToDecimalSSPHHonde(uint16_t hexData) {
  float hexDecimal = 0;
  char hexArray[5];
  sprintf(hexArray, "%04X", hexData);
  uint16_t hexInt = (uint16_t)strtol(hexArray, NULL, 16);
  hexDecimal = hexInt / 1.0;
  return hexDecimal;
}
//uint16_t CLASS_SSPHHonde::CombineHexSSPHHonde(uint8_t *hexArray) {
//  Serial.println("Combine Decimal");
//  uint16_t hexCombine = 0;
//  hexCombine |= hexArray[0];
//  hexCombine <<= 8;
//  hexCombine |= hexArray[1];
//  hexCombine <<= 8;
//  return hexCombine;
//}
