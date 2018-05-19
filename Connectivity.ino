/*
 * This tab includes all the setup information for the MQTT initialisation and transmission
 * 
 */
MQTT_Packets MQTT_Packets_Object(&commsif);
mqtt_client_info ClientInfo;
mqtt_message LastWillMessage;
mqtt_message PublishMessage;
mqtt_topic SubscribeList[2];


bool connected;
char TOPIC[128];
char CONTENT[255];
char MainBuffer[1024];
#define HOST "TIC2018.azure-devices.net"
#define PORT 8883
#define DeviceName "TIC2018_Demo"

/*
 * Set all the necessary flags to establish an MQTT connection with Azure
 */
bool initialize_my_mqtt() {
  ClientInfo.client_id = DeviceName;
  ClientInfo.keep_alive_sec = 60;
  ClientInfo.clean_session = true;
  ClientInfo.tls = true;
  ClientInfo.username_flag = true;
  ClientInfo.password_flag = true;
  ClientInfo.will_flag = false;
  ClientInfo.username = "TIC2018.azure-devices.net/TIC2018_Demo/api-version=2016-11-14";
  ClientInfo.password = "SharedAccessSignature sr=xxxxxxxxxxxxxx";

  LastWillMessage.topic = "devices/TIC2018_Demo/messages/events/LastWillTopc";
  LastWillMessage.content = "LastWillContent";
  LastWillMessage.qos = 0;
  LastWillMessage.retain = false;

  PublishMessage.topic = "devices/TIC2018_Demo/messages/events/";
  PublishMessage.content = "{ \"hello\": \"world\"}";
  PublishMessage.qos = 0;
  PublishMessage.retain = false;

  SubscribeList[0].topic = "devices/TIC2018_Demo/messages/devicebound/#";
  SubscribeList[0].qos = 1;

  return true;
}

/*
 * Take the initialised information and establishes a connection to IoT Hub
 */
bool connectToIoTHub() {
  Serial.println("***Sending Connect Command***");
  int res = MQTT_Packets_Object.Connect(HOST, PORT, &ClientInfo, &LastWillMessage);

  if (res < 0) {
    Serial.println("ERROR: Connection could not be established. Error code: ");
    Serial.println(res);
    return false;
  } else {
    Serial.println("Success: Connection to IoT Hub established");
    return true;
  }
}

/*
 * Send constructed message payload to IoT Hub
 */
void sendMeasurementsToIoTHub(String sensorMeasurements){
  char pubmessage_c[200];
  String payloadMessage= "{ \"sensor_id\": \"TIC2018_Demo\", ";
  int resp;
  
  payloadMessage+=sensorMeasurements;
  payloadMessage+="}\n";

  Serial.println("***Printing Message***");
  Serial.println(payloadMessage);

  payloadMessage.toCharArray(pubmessage_c,payloadMessage.length()) ;
  PublishMessage.content = pubmessage_c;
  resp=MQTT_Packets_Object.Publish(&PublishMessage);

  if (resp==0) {
    Serial.println(">>Message Successfully Sent");
  } else {
    Serial.println("ERROR: Message not sent. Error code: ");
    Serial.println(resp);
  }
 
}


