#include "I2C_TSL.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
Adafruit_TSL2561_Unified ts1 = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

bool CLASS_I2CTSL::SETUP() {
  Serial.print("vào khởi tạo i2");
  if (!ts1.begin())
  {
    Serial.print("Ooops, no TSL2561-1 detected ... Check your wiring or I2C ADDR!");
    delay(1000);
    return 0;
  }
  delay(100);
  ts1.enableAutoRange(true);
  ts1.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);
  Serial.print("khởi tạo i2c ok");
  return 1;
}

void CLASS_I2CTSL::RUNNING(uint16_t &value) {
  delay(100);
  uint32_t val = 0;
  for (uint8_t i = 0 ; i < 5; i++) {
    sensors_event_t event1;
    ts1.getEvent(&event1);
    val += event1.light;
    delay(10);
  }
  //Serial.println( String(val / 5));
  value = val / 5;
  return;

}
