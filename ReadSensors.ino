/*
 * This tab includes all the functions for reading sensors
 * 
 */

 /*
  * Aggregates message reading functions and new measurements here
  */
String readSensorMeasurements() {  
  char* totalMessage;
  String bufferMessage;

  bufferMessage = readAccelSensor();

  //readTempSensor()
  //readLightSensor()

  Serial.println(">>Message");
  Serial.println(bufferMessage);

  return(bufferMessage);

}

/*
 * Reads measurements from accelerometer and formats JSON string
 */
String readAccelSensor() {
  char ax_string[10];
  char ay_string[10];
  char az_string[10];
  String formattedAccelMeasurements;

  Serial.println("***Reading Accelerometer***");
  if (accel.available()) {
    accel.read();
    dtostrf(accel.cx, 2, 3, ax_string);
    dtostrf(accel.cy, 2, 3, ay_string);
    dtostrf(accel.cz, 2, 3, az_string);

    formattedAccelMeasurements = "\"accelerometer_x\": \"";
    formattedAccelMeasurements += accel.cx;
    
    formattedAccelMeasurements += "\", \"accelerometer_y\": \"";
    formattedAccelMeasurements += accel.cy;
    
    formattedAccelMeasurements += "\", \"accelerometer_z\": \"";
    formattedAccelMeasurements += accel.cz;
    formattedAccelMeasurements += "\"";


    return formattedAccelMeasurements;
  }  

  return("nothing");
  
}

//char* readTempSensor() {
//
//  temperature = random(13, 15)+(random(1, 99)*0.01);
//  
//}
//
//char* readLightSensor() {
//  light = random(100, 300)+(random(1, 99)*0.01);
//}


// The function demonstrates how to use the accel.x, accel.y and
//  accel.z variables.
// Before using these variables you must call the accel.read()
//  function!
void printAccels()
{
  Serial.print(accel.x, 3);
  Serial.print("\t");
  Serial.print(accel.y, 3);
  Serial.print("\t");
  Serial.print(accel.z, 3);
  Serial.print("\t");
}

// This function demonstrates how to use the accel.cx, accel.cy,
//  and accel.cz variables.
// Before using these variables you must call the accel.read()
//  function!
void printCalculatedAccels()
{ 
  Serial.print(accel.cx, 3);
  Serial.print("\t");
  Serial.print(accel.cy, 3);
  Serial.print("\t");
  Serial.print(accel.cz, 3);
  Serial.print("\t");
}
