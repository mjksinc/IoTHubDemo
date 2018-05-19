/*
 * This tab contains all of the primary information and core functions to run the program. All headers are defined in this tab Below
 * is an index of other tabs:
 * - Connectivity: This tab includes all the setup information for the MQTT initialisation and transmission
 * - ReadSensors: Contains all the code to read from the on-board sensors
 */

// MARK: Libraries for Board
#include <telstraiot.h>
#include <TelstraM1Device.h>
#include <TelstraM1Interface.h>
#include <stdlib.h>
#include <avr/dtostrf.h>

// MARK: Libraries for Connectivity
#include <mqttpackets.h>

// MARK: Libraries for Sensors
#include <Wire.h> // Must include Wire library for I2C (ACCELEROMETER)
#include <SparkFun_MMA8452Q.h> // Includes the SFE_MMA8452Q library (ACCELEROMETER)

// MARK: Definitions
#define BUTTON 7
#define LED 13

// MARK: Initialisations
TelstraM1Interface commsif;
TelstraM1Device IoTDevice(&commsif);
MMA8452Q accel;

// MARK: Set up function
void setup() {
  // Variable Declaration
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW); 
  commsif.begin(); // Must include for proper SPI 
  Serial.begin(115200);
  while(!Serial);
  bool mqttSuccess = false;
  
  Serial.println("***Starting Program***");

  // Initialise Accelerometer
  Serial.println("***Initialise Accelerometer***");
  accel.init();

  // Initialise MQTT
  Serial.println("***Initialise MQTT***");
  mqttSuccess = initialize_my_mqtt();

  // Connect to IoT Hub
  if(mqttSuccess) {
    if (connectToIoTHub()) {
      Serial.println("Success: Connected to IoT Hub");
    } else {
      Serial.println("ERROR: Could not initialise MQTT");
    }
  }
}

// MARK: Beginning of loop
void loop() {
  // Read measurements from the board
  String measurementReadings = readSensorMeasurements();

  // Send message payload to IoT Hub
  sendMeasurementsToIoTHub(measurementReadings);

  // Repeat every 5 seconds
  delay(5000);
}


