/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/lingxiu/Documents/0-documents/2023-2024-MDes/TDF/tdf-fa23-rocketcrane/ADXL_362/src/ADXL_362.ino"
//TEST CODE FOR Pillow Music Project
//Lingxiu 
//Oct 2023
//#include "Particle.h" //from BLE code
#include "BleLogging.h" //logging for BLE

#include "ADXL362.h"
void setup();
void loop();
#line 8 "/Users/lingxiu/Documents/0-documents/2023-2024-MDes/TDF/tdf-fa23-rocketcrane/ADXL_362/src/ADXL_362.ino"
ADXL362 adxl362;

SerialLogHandler logHandler;

//static int deviceID = 0; //used to differentiate between multiple devices

SYSTEM_THREAD(ENABLED); //IMPORTANT for all Particle devices
//SYSTEM_MODE(MANUAL); //for non-cloud connected mode

//BLE UUIDs for IMU example
// const BleUuid serviceUuid("a2916c31-22b3-4284-93ba-8a784fa0baff");
// const BleUuid valueUuid("b871bee1-e621-40db-8d31-4c86b2acfebb");

// BleCharacteristic valueCharacteristic("value", BleCharacteristicProperty::NOTIFY, valueUuid, serviceUuid); //IMU example

//BLE variables for IMU example
// const unsigned long UPDATE_PERIOD_MS = 100;
// unsigned long lastUpdate = 0;
//struct for sample data
// typedef union {
// 	struct {
// 		int x;
//     int y;
//     int z;
//     //float r;
//     //float p;
//     //float t;
// 	} sample;
// 	uint8_t bytes[12];
// } Sample;

void setup() {
  //DEBUGGING
  //Serial.begin(9600);
  //waitFor(Serial.isConnected, 15000);
  //Log.info("Serial connected or timed out!");

  adxl362.begin();
  adxl362.beginMeasure(); //NECESSARY - starts measurement

  adxl362.setRange(XL362_FILTER_FLAG_8G); //sets range to 8G - other options are 2G and 4G

  // //BLE setup for IMU example
  // BLE.addCharacteristic(valueCharacteristic);
	// BleAdvertisingData data;
	// data.appendServiceUUID(serviceUuid);
	// BLE.advertise(&data);
}


void loop() {
  int x, y, z;
  float r, p, t;

  //static unsigned long lastTime = 0; // initialize to starting time
  //unsigned long currentTime = millis(); // get time since start of program

  adxl362.readXYZmg(x, y, z); //burst read of axes - REQUIRED to guarantee all measurements correspond to same sample time 
  adxl362.XYZmgtoRPT(x, y, z, r, p, t); //converts raw data to roll, pitch, tilt

  //BLE loop code for IMU example
  // if (BLE.connected()) {
	// 	if (millis() - lastUpdate >= UPDATE_PERIOD_MS) {
	// 		lastUpdate = millis();

	// 		Sample sample;
	// 		//sample.sample.x = x;
	// 		//sample.sample.y = y;
	// 		//sample.sample.z = z;
  //     //sample.sample.r = r;
  //     //sample.sample.p = p;
  //     //sample.sample.t = t;
  //     sample.sample.x = r;
  //     sample.sample.y = p;
  //     sample.sample.z = t;

	// 		valueCharacteristic.setValue(sample.bytes, sizeof(Sample));
	// 	}
  //}
  /*
  if (currentTime - lastTime >= 1000) { // execute the following block of code every second, because, to quote the Particle docs:
  //Currently, a device can publish at rate of about 1 event/sec, with bursts of up to 4 allowed in 1 second. Back to back burst of 4 messages will take 4 seconds to recover.
  //Each publish uses one Data Operation from your monthly or yearly quota. (This means we'll run out of data operations in 100,000/60/60 = 27 minutes!)
    lastTime = currentTime; // update lastTime to current time

    String message = String(deviceID) + ", " + String(x) + ", " + String(y) + ", " + String(z) + ", " + String(r) + ", " + String(p) + ", " + String(t);

    if(!Particle.publish(message)) {
      Log.info("Publish failed! You might not be connected to WiFi or the Particle Cloud.");
    }
  }
  */

  //Log.info("x: %d, y: %d, z: %d, r: %f, p: %f, t: %f", x, y, z, r, p, t);
  //Serial.printlnf("%d, %d, %d, %f, %f, %f", x, y, z, r, p, t); //DEBUGGING - Use Arduino Serial Plotter
  //Serial.printlnf("%f, %f, %f", r, p, t); //DEBUGGING - Use Arduino Serial Plotter
  //delay(1); //for DEBUGGING
}