/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/lingxiu/Documents/0-documents/2023-2024-MDes/TDF/ADXL_362/src/ADXL_362.ino"
void setup();
void loop();
#line 1 "/Users/lingxiu/Documents/0-documents/2023-2024-MDes/TDF/ADXL_362/src/ADXL_362.ino"
SerialLogHandler logHandler;
#include "ADXL362.h"
ADXL362 adxl362;

void setup() {
  //DEBUGGING
  Serial.begin(9600);
  waitFor(Serial.isConnected, 15000);
  Log.info("Serial connected or timed out!");

  adxl362.begin();
  adxl362.beginMeasure(); //NECESSARY - starts measurement
}


void loop() {
  int x1, y1, z1;
  short x, y, z;
  float t;

  adxl362.readXYZmg(x1, y1, z1); //burst read of axes - REQUIRED to guarantee all measurements correspond to same sample time 
  adxl362.readXYZTData(x, y, z, t); //burst read of all registers - REQUIRED to guarantee all measurements correspond to same sample time

  Log.info("x: %d, y: %d, z: %d, t: %d", x, y, z, t);
  delay(500);
}