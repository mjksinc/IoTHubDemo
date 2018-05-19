/*
 * This tab includes all the functions for reading sensors
 * 
 */

 /*
  * Aggregates message reading functions and new measurements here
  */
String readSensorMeasurements() {  
  String totalMessage;
  String bufferMessage;

  bufferMessage = readAccelSensor();
  totalMessage+=bufferMessage;
  
  bufferMessage = readTempSensor();
  totalMessage+=bufferMessage;

  bufferMessage = readLightSensor();
  totalMessage+=bufferMessage;

  Serial.println(">>Message");
  Serial.println(totalMessage);

  return(totalMessage);

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

String readTempSensor() {
  char temperature[15];
  String formattedTempMeasurements;

  Serial.println("***Reading Temperature***");
  IoTDevice.getTemperature(temperature);

  formattedTempMeasurements = ", \"temperature\": \"";
  formattedTempMeasurements+= temperature;
  formattedTempMeasurements += "\"";

  return formattedTempMeasurements;
  
}

String readLightSensor() {
  char lightReading[15];
  String formattedLightMeasurements;

  Serial.println("***Reading Light***");
  IoTDevice.getLightLevel(lightReading);

  formattedLightMeasurements = ", \"light\": \"";
  formattedLightMeasurements+= lightReading;
  formattedLightMeasurements += "\"";

  return formattedLightMeasurements;
}


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
