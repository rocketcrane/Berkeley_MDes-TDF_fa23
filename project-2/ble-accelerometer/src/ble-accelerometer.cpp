/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/lingxiu/Documents/0-documents/2023-2024-MDes/TDF/tdf-fa23-rocketcrane/ble-accelerometer/src/ble-accelerometer.ino"
#include "blelogging.h"


// This demo works better with system thread enabled, otherwise the BLE log handler is not
// initialized until you've already connected to the cloud, which is not as useful.
void setup();
void loop();
#line 6 "/Users/lingxiu/Documents/0-documents/2023-2024-MDes/TDF/tdf-fa23-rocketcrane/ble-accelerometer/src/ble-accelerometer.ino"
SYSTEM_THREAD(ENABLED);

// This sets up the BLE log handler. The <4096> template parameter sets the size of the buffer to hold log data
// The other parameters are like SerialLogHandler. You can set the log level (optional) to things like
// LOG_LEVEL_ALL, LOG_LEVEL_TRACE, LOG_LEVEL_DEBUG, LOG_LEVEL_INFO, etc.. You can also pass a log filter here.
BleLogging<4096> bleLogHandler(LOG_LEVEL_WARN);

// Optionally you can also enable USB serial log handling (or other log handlers, as desired).
//SerialLogHandler serialLogHandler(LOG_LEVEL_WARN);

const unsigned long LOG_INTERVAL = 100; // how often to log messages
unsigned long lastLog = 0;

// accelerometer setup
#include "ADXL362.h"
ADXL362 adxl362;

void setup() {
	BLE.on();

	// You must add this to your setup() to initialize the library
	bleLogHandler.setup();

	 // necessary - starts accelerometer measurement
	adxl362.begin();
  	adxl362.beginMeasure();
	adxl362.setRange(XL362_FILTER_FLAG_8G); //sets range to 8G - other options are 2G and 4G
}

void loop() {
	// You must add this to your loop to process BLE requests and data
	bleLogHandler.loop();

	// accelerometer variables
	int x, y, z;
  	float r, p, t;

	adxl362.readXYZmg(x, y, z); // burst read of axes - REQUIRED to guarantee all measurements correspond to same sample time 
  	adxl362.XYZmgtoRPT(x, y, z, r, p, t); // converts raw data to roll, pitch, tilt

	if (millis() - lastLog >= LOG_INTERVAL) {
		lastLog = millis();

		Log.warn("x: %d, y: %d, z: %d, r: %f, p: %f, t: %f", x, y, z, r, p, t); // all the data!
	}
}