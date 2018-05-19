# IoTHubDemo

This repo includes all the code needed to connect you TIC2018 IoT Device to Azure and display the data stream using a web app.


IoTHubDemo includes three files:
  - IoTHubDemo is the primary file that contains headers, initialisations, setup and loop functions
  - Conntectivity contains all the requisite code for configuring the MQTT link to IoT Hub #NOTE# this is where you will put all your IoT Hub information
  - ReadSensors contains all the code for reading measurements from the board and constructing the measurement portion of the payload string
 
Azure-Web-App-IoT contains all the code to load onto your web server to graph the measurements. Replace the default code in the Web App guide below with this code.


These guides will help you get started:
  - This link walks through setting up IoT Hub (you can ignore the device code in this doc): https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-raspberry-pi-kit-node-get-started 
  - This link guides you to initialising a web app in Azure, connecting it to Azure and deploying: https://docs.microsoft.com/en-us/azure/iot-hub/iot-hub-live-data-visualization-in-web-apps
  
For more info on the IoT Board, head on over to the TIC2018 repo: https://github.com/telstra/TIC2018 


# Other useful links
  - An easy way to manade devices is with the Device Explorer. This will help you monitor events, create SAS Tokens, and gather all the information you neec to edit the Connectivity.ino file: https://github.com/Azure/azure-iot-sdk-csharp/tree/master/tools/DeviceExplorer
  - Storage explorer lets you search through tables for data: https://azure.microsoft.com/en-us/features/storage-explorer/
