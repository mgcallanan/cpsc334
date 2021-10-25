#include "WiFi.h"
#include <WiFiudp.h>

int pizoelectric = 34;

// WiFi network name and password:
const char * networkName = "yale wireless";
const char * networkPswd = "";

const char *softAPNetworkName = "MaryESP32AP";
const char *softAPNetworkPswd = "BeCre@tive!";

// IP Address and port of laptop over which to send UDP data

// Mary Laptop IP
const char * laptopudpAddress = "172.29.16.220";
const int laptopudpPort = 8092;

// Maansi Laptop IP
//const char * laptopudpAddress = "172.20.10.2";
//const int laptopudpPort = 8092;

//Are we currently connected?
boolean connected = false;

//The udp library class
WiFiUDP udp;

// For receiving UDP messages from other ESP32

// local port to listen on
unsigned int localPort = 8088;

// buffer to hold incoming packet
char packetBuffer[255];

byte command[27] = {0x20, 0x00, 0x00, 0x00, 0x16, 0x02, 0x62, 0x3A, 0xD5, 0xED, 0xA3, 0x01, 0xAE, 0x08, 0x2D, 0x46, 0x61, 0x41, 0xA7, 0xF6, 0xDC, 0xAF, 0xD3, 0xE6, 0x00, 0x00, 0x1E};

void setup(){
  
  // Initilize hardware serial:
  Serial.begin(115200);

  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd, softAPNetworkName, softAPNetworkPswd);
}

void loop(){
  int maryPiezoValue = analogRead(pizoelectric);
  // Serial.println(maryPiezoValue);
  int maansiPiezoValue = random(4096);
  int distance = random(5);

  
  delay(100);
  
  // Only send/receive UDP data when connected to WiFi
  if(connected){

      // Check to see if receiving any UDP packets from other ESP32
      int packetSize = udp.parsePacket();
      
      if (packetSize) {    
        int len = udp.read(packetBuffer, 255);
    
        if (len > 0) {
          packetBuffer[len] = 0;
        }
    
        Serial.println("RSSI:");
    
        Serial.println(packetBuffer);
      }

    //Send a packet to laptop with distance and piezo values
    udp.beginPacket(laptopudpAddress,laptopudpPort);
    udp.print(String(maryPiezoValue) + "," + String(maansiPiezoValue) + "," + String(packetBuffer));
    udp.endPacket();
  }
  //Wait for 1 second
  delay(10);
}

void connectToWiFi(const char * ssid, const char * pwd, const char * soft_ap_ssid, const char * soft_ap_pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);
  
  // Set up soft AP and station mode
  WiFi.mode(WIFI_MODE_APSTA);
 
  WiFi.softAP(soft_ap_ssid, soft_ap_pwd);
  
  //Initiate connection
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.print("ESP32 IP as soft AP: ");
  Serial.println(WiFi.softAPIP());
 
  Serial.print("ESP32 IP on the WiFi network: ");
  Serial.println(WiFi.localIP());

  udp.begin(localPort);
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          //initializes the UDP state
          //This initializes the transfer buffer
          udp.begin(WiFi.localIP(),laptopudpPort);
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
    }
}
