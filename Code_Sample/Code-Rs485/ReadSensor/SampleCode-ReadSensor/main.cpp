#include "main.h"
CLASS_SSR Renke;
CLASS_SSDODisen Disen;
CLASS_SSDOY505 Y505;
CLASS_SSPHSuprama Suprama;
CLASS_SSPHHonde Honde;
CLASS_SSSalinityDaxi Daxi;
void class_main::Setup() {
  Renke.SetupSSR();
  Disen.SetupSSDODisen( );
  Y505.SetupSSDOY505();
  Honde.SetupSSPHHonde();
  Suprama.SetupSSPHSuprama( );
  Daxi.SetupSSSalinityDaxi( );
  return;
}
bool class_main::Running(char *typeSensor) {
  float para = 0;
  float temp = 0;
  bool done = false;
  if (typeSensor == "sensorRenke")
    done = Renke.RunningSSR(para, temp);
  else if (typeSensor == "sensorDisen")
    done = Disen.RunningSSDODisen(para, temp);
  else if (typeSensor == "sensorY505")
    done = Y505.RunningSSDOY505(para, temp);
  else if (typeSensor == "sensorHonde")
    done = Honde.RunningSSPHHonde(para, temp);
  else if (typeSensor == "sensorSuprama")
    done = Suprama.RunningSSPHSuprama(para, temp);
  else if (typeSensor == "sensorDaxi")
    done = Daxi.RunningSSSalinityDaxi(para, temp);

  return done;
}
