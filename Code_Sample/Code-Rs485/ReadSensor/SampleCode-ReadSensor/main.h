#ifndef main_h
#define main_h
//#include "CONFIGPIN.h"
#include "SSRenke.h"
#include "SSPHSuprama.h"
#include "SSSalinityDaxi.h"
#include "SSPHHonde.h"
#include "SSDOY505.h"
#include "SSDODisen.h"
class class_main {
  private:

  public:
    void Setup();
    void Running(char *typeSensor);
};
#endif;
