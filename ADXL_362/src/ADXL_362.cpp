/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/lingxiu/Documents/0-documents/2023-2024-MDes/TDF/tdf-fa23-rocketcrane/ADXL_362/src/ADXL_362.ino"
//TEST CODE FOR ADXL362 ACCELEROMETER
//Lingxiu

void setup();
void loop();
#line 4 "/Users/lingxiu/Documents/0-documents/2023-2024-MDes/TDF/tdf-fa23-rocketcrane/ADXL_362/src/ADXL_362.ino"
SerialLogHandler logHandler;

#include "ADXL362.h"
ADXL362 adxl362;

static int deviceID = 0; //used to differentiate between multiple devices

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
  int x, y, z;
  float r, p, t;

  static unsigned long lastTime = 0; // initialize to starting time
  unsigned long currentTime = millis(); // get time since start of program

  adxl362.readXYZmg(x, y, z); //burst read of axes - REQUIRED to guarantee all measurements correspond to same sample time 
  adxl362.XYZmgtoRPT(x, y, z, r, p, t); //converts raw data to roll, pitch, tilt

  if (currentTime - lastTime >= 1000) { // execute the following block of code every second, because, to quote the Particle docs:
  //Currently, a device can publish at rate of about 1 event/sec, with bursts of up to 4 allowed in 1 second. Back to back burst of 4 messages will take 4 seconds to recover.
  //Each publish uses one Data Operation from your monthly or yearly quota. (This means we'll run out of data operations in 100,000/60/60 = 27 minutes!)
    lastTime = currentTime; // update lastTime to current time

    String message = String(deviceID) + ", " + String(x) + ", " + String(y) + ", " + String(z) + ", " + String(r) + ", " + String(p) + ", " + String(t);

    if(!Particle.publish(message)) {
      Log.info("Publish failed! You might not be connected to WiFi or the Particle Cloud.");
    }
  }

  //Log.info("x: %d, y: %d, z: %d, r: %f, p: %f, t: %f", x, y, z, r, p, t);
  //Serial.printlnf("%d, %d, %d, %f, %f, %f", x, y, z, r, p, t); //DEBUGGING - Use Arduino Serial Plotter
  //Serial.printlnf("%f, %f, %f", r, p, t); //DEBUGGING - Use Arduino Serial Plotter
  //delay(1); //for DEBUGGING
}