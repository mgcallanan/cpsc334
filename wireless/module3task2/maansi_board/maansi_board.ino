#include "WiFi.h"
#include <WiFiUdp.h>

int piezo = 35;

// WiFi network name and password:
//const char * networkName = "yale wireless";
//const char * networkPswd = "";

// WiFi network name and password of hotspot created by the other ESP32
const char * networkName = "MaryESP32AP";
const char * networkPswd = "BeCre@tive!";

// IP Address of the other ESP32 to send UDP messages over
const char * espUdpAddress = "192.168.4.1";
const int espUdpPort = 8088;

// Are we currently connected?
boolean connected = false;

// The UDP library class
WiFiUDP udp;

byte command[27] = {0x20, 0x00, 0x00, 0x00, 0x16, 0x02, 0x62, 0x3A, 0xD5, 0xED, 0xA3, 0x01, 0xAE, 0x08, 0x2D, 0x46, 0x61, 0x41, 0xA7, 0xF6, 0xDC, 0xAF, 0xD3, 0xE6, 0x00, 0x00, 0x1E};

void setup(){
  pinMode(photoResistor, INPUT);
  
  // Initilize hardware serial:
  Serial.begin(115200);

  //Connect to the WiFi network
   connectToWiFi(networkName, networkPswd);
}

void loop(){
  // Uncomment when piezoelectric functionality is added
  // float pie = analogRead(piezo);
  // Serial.print("pie ");
  // Serial.println(pie);

  // Get signal time a.k.a distance from other ESP32 serving as access board
  long rssi = WiFi.RSSI();
  Serial.print("RSSI:");
  Serial.println(rssi);
  
  if (connected) {
    // Send RSSI values back to ESP32 hotspot to serve as distance values
    udp.beginPacket(espUdpAddress,espUdpPort);
    udp.print(String(rssi));
    udp.endPacket();
  }
  
  //Wait for 1 second
  delay(10);
}

void connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);

  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          
          // Starts UDP system and initializes transfer buffer
          udp.begin(WiFi.localIP(),espUdpPort);
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
    }
}
