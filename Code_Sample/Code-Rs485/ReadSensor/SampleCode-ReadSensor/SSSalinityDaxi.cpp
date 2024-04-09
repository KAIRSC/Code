#include "SSSalinityDaxi.h"
CLASS_SENSOR485 SSSalinityDaxiSENSOR485;
void CLASS_SSSalinityDaxi::Func_SetupSSSalinityDaxi() {
  RunningFuncSSSalinityDaxi = &CLASS_SSSalinityDaxi::Func_Read485SSSalinityDaxi;
}
bool CLASS_SSSalinityDaxi::Func_RunningSSSalinityDaxi(float *para, float *temp) {
  bool doneMain = (this ->*RunningFuncSSSalinityDaxi)();
  if (doneMain) {
    *para = p_paraSSSalinityDaxi;
    *temp = p_tempSSSalinityDaxi;
  }
  return doneMain;
}
bool CLASS_SSSalinityDaxi::Func_Read485SSSalinityDaxi() {
  bool done = SSSalinityDaxiSENSOR485.Func_Running485(p_requestFrameSSSalinityDaxi, sizeof(p_requestFrameSSSalinityDaxi), p_respondFrameSSSalinityDaxi, sizeof(p_respondFrameSSSalinityDaxi) / sizeof(uint16_t));
  p_paraSSSalinityDaxi = 0;
  p_tempSSSalinityDaxi = 0;
  if (done) {
    RunningFuncSSSalinityDaxi = &CLASS_SSSalinityDaxi::Func_GetParaSSSalinityDaxi;
  }
  return 0;
}
bool CLASS_SSSalinityDaxi::Func_GetParaSSSalinityDaxi() {
  uint16_t hexPara = p_respondFrameSSSalinityDaxi[0];
  uint16_t hexDecimalPara = p_respondFrameSSSalinityDaxi[1];
  uint16_t hexTemp = p_respondFrameSSSalinityDaxi[2];
  uint16_t hexDecimalTemp = p_respondFrameSSSalinityDaxi[3];
  p_paraSSSalinityDaxi = Func_HexToDecimalSSSalinityDaxi(hexPara);
  p_tempSSSalinityDaxi = Func_HexToDecimalSSSalinityDaxi(hexTemp);
  for (int i = 0 ; i < Func_HexToDecimalSSSalinityDaxi(hexDecimalPara) ; i++) {
    p_paraSSSalinityDaxi /= 10;
  }
  for (int i = 0 ; i < Func_HexToDecimalSSSalinityDaxi(hexDecimalTemp) ; i++) {
    p_tempSSSalinityDaxi /= 10;
  }
  //p_tempSSSalinityDaxi = Func_HexToDecimalSSSalinityDaxi(hexTemp) / (10 * Func_HexToDecimalSSSalinityDaxi(hexDecimalTemp));
  RunningFuncSSSalinityDaxi = &CLASS_SSSalinityDaxi::Func_Read485SSSalinityDaxi;
  return 1;
}
float CLASS_SSSalinityDaxi::Func_HexToDecimalSSSalinityDaxi(uint16_t hexData) {
  float hexDecimal = 0;
  char hexArray[5];
  sprintf(hexArray, "%04X", hexData);
  uint16_t hexInt = (uint16_t)strtol(hexArray, NULL, 16);
  hexDecimal = hexInt / 1.0;
  return hexDecimal;
}
