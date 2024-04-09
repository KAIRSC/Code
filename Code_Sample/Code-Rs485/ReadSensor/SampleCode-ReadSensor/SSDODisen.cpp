#include "SSDODisen.h"
CLASS_SENSOR485 SSDODisenSENSOR485;
void CLASS_SSDODisen::SetupSSDODisen() {
  RunningFuncSSDODisen = &CLASS_SSDODisen::Read485SSDODisen;
}
bool CLASS_SSDODisen::RunningSSDODisen(float &para, float &temp) {
  bool doneMain = (this ->*RunningFuncSSDODisen)();
  if (doneMain) {
    para = p_paraSSDODisen;
    temp = p_tempSSDODisen;
  }
  return doneMain;
}
bool CLASS_SSDODisen::Read485SSDODisen() {
  bool done = SSDODisenSENSOR485.Running485_2(p_requestFrameSSDODisen, sizeof(p_requestFrameSSDODisen), p_respondFrameSSDODisen, sizeof(p_respondFrameSSDODisen) / sizeof(uint16_t));
  p_paraSSDODisen = 0;
  p_tempSSDODisen = 0;
  if (done) {
    RunningFuncSSDODisen = &CLASS_SSDODisen::GetParaSSDODisen;
  }
  return 0;
}
bool CLASS_SSDODisen::GetParaSSDODisen() {
  uint8_t hexParaArray[4] = {0};
  uint8_t  hexTempArray[4] = {0};
  for (uint8_t i = 0 ; i < 4 ; i++) {
    hexParaArray[i] = p_respondFrameSSDODisen[14 - i];
    hexTempArray[i] = p_respondFrameSSDODisen[6 - i];
  }
  uint32_t hexPara = CombineHexSSDODisen(hexParaArray);
  uint32_t hexTemp = CombineHexSSDODisen(hexTempArray);
  p_paraSSDODisen = HexToFloatSSDODisen(hexPara);
  p_tempSSDODisen = HexToFloatSSDODisen(hexTemp);
  RunningFuncSSDODisen = &CLASS_SSDODisen::Read485SSDODisen;
  return 1;
}
float CLASS_SSDODisen::HexToFloatSSDODisen(uint32_t hexData) {
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
uint32_t CLASS_SSDODisen::CombineHexSSDODisen(uint8_t *hexArray) {
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
