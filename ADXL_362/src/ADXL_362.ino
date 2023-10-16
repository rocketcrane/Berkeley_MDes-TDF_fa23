//TEST CODE FOR ADXL362 ACCELEROMETER
//Lingxiu

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

  adxl362.setRange(XL362_FILTER_FLAG_8G); //sets range to 8G - other options are 2G and 4G
}


void loop() {
  //float time;
  int x, y, z;
  float r, p, t;

  adxl362.readXYZmg(x, y, z); //burst read of axes - REQUIRED to guarantee all measurements correspond to same sample time 
  //adxl362.readXYZTData(x, y, z, time); //burst read of all registers - REQUIRED to guarantee all measurements correspond to same sample time
  adxl362.XYZmgtoRPT(x, y, z, r, p, t); //converts raw data to roll, pitch, tilt

  int roll = (int)r;
  int pitch = (int)p;
  int tilt = (int)t;

  //Log.info("x: %d, y: %d, z: %d, r: %d, p: %d, t: %d", x, y, z, roll, pitch, tilt);
  //Serial.printlnf("%d, %d, %d, %d, %d, %d", x, y, z, roll, pitch, tilt); //DEBUGGING - Use Arduino Serial Plotter
  //Serial.printlnf("%d, %d, %d", roll, pitch, tilt); //DEBUGGING - Use Arduino Serial Plotter
  delay(1);
}