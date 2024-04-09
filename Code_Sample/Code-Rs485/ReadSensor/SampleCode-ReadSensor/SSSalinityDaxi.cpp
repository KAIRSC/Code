#include "SSSalinityDaxi.h"
CLASS_SENSOR485 SSSalinityDaxiSENSOR485;
void CLASS_SSSalinityDaxi::SetupSSSalinityDaxi() {
  RunningFuncSSSalinityDaxi = &CLASS_SSSalinityDaxi::Read485SSSalinityDaxi;
}
bool CLASS_SSSalinityDaxi::RunningSSSalinityDaxi(float &para, float &temp) {
  bool doneMain = (this ->*RunningFuncSSSalinityDaxi)();
  if (doneMain) {
     para = p_paraSSSalinityDaxi;
     temp = p_tempSSSalinityDaxi;
  }
  return doneMain;
}
bool CLASS_SSSalinityDaxi::Read485SSSalinityDaxi() {
  bool done = SSSalinityDaxiSENSOR485.Running485(p_requestFrameSSSalinityDaxi, sizeof(p_requestFrameSSSalinityDaxi), p_respondFrameSSSalinityDaxi, sizeof(p_respondFrameSSSalinityDaxi) / sizeof(uint16_t));
  p_paraSSSalinityDaxi = 0;
  p_tempSSSalinityDaxi = 0;
  if (done) {
    RunningFuncSSSalinityDaxi = &CLASS_SSSalinityDaxi::GetParaSSSalinityDaxi;
  }
  return 0;
}
bool CLASS_SSSalinityDaxi::GetParaSSSalinityDaxi() {
  uint16_t hexPara = p_respondFrameSSSalinityDaxi[0];
  uint16_t hexDecimalPara = p_respondFrameSSSalinityDaxi[1];
  uint16_t hexTemp = p_respondFrameSSSalinityDaxi[2];
  uint16_t hexDecimalTemp = p_respondFrameSSSalinityDaxi[3];
  p_paraSSSalinityDaxi = HexToDecimalSSSalinityDaxi(hexPara);
  p_tempSSSalinityDaxi = HexToDecimalSSSalinityDaxi(hexTemp);
  for (int i = 0 ; i < HexToDecimalSSSalinityDaxi(hexDecimalPara) ; i++) {
    p_paraSSSalinityDaxi /= 10;
  }
  for (int i = 0 ; i < HexToDecimalSSSalinityDaxi(hexDecimalTemp) ; i++) {
    p_tempSSSalinityDaxi /= 10;
  }
  //p_tempSSSalinityDaxi = HexToDecimalSSSalinityDaxi(hexTemp) / (10 * HexToDecimalSSSalinityDaxi(hexDecimalTemp));
  RunningFuncSSSalinityDaxi = &CLASS_SSSalinityDaxi::Read485SSSalinityDaxi;
  return 1;
}
float CLASS_SSSalinityDaxi::HexToDecimalSSSalinityDaxi(uint16_t hexData) {
  float hexDecimal = 0;
  char hexArray[5];
  sprintf(hexArray, "%04X", hexData);
  uint16_t hexInt = (uint16_t)strtol(hexArray, NULL, 16);
  hexDecimal = hexInt / 1.0;
  return hexDecimal;
}
