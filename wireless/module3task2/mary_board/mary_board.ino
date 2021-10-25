#include "WiFi.h"
#include <WiFiUdp.h>

int pizoelectric = 34;

// WiFi network name and password:
const char * networkName = "yale wireless";
const char * networkPswd = "";

const char *softAPNetworkName = "MaryESP32AP";
const char *softAPNetworkPswd = "BeCre@tive!";

//IP address to send UDP data to:
// either use the ip address of the server or 
// a network broadcast address

const char * udpAddress = "172.29.28.52";
const int udpPort = 8090;

//Are we currently connected?
boolean connected = false;

//The udp library class
WiFiUDP udp;

byte command[27] = {0x20, 0x00, 0x00, 0x00, 0x16, 0x02, 0x62, 0x3A, 0xD5, 0xED, 0xA3, 0x01, 0xAE, 0x08, 0x2D, 0x46, 0x61, 0x41, 0xA7, 0xF6, 0xDC, 0xAF, 0xD3, 0xE6, 0x00, 0x00, 0x1E};

void setup(){
  
  // Initilize hardware serial:
  Serial.begin(115200);

  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd, softAPNetworkName, softAPNetworkPswd);
}

void loop(){
  int maryPizoValue = analogRead(pizoelectric);
  Serial.println(maryPizoValue);
  int maansiPizoValue = random(4096);
  int distance = random(5);
//  Serial.print("Stations connected: ");
//  Serial.println(WiFi.softAPgetStationNum());
  delay(100);
  //only send data when connected
  if(connected){
    //Send a packet
    udp.beginPacket(udpAddress,udpPort);
    udp.print(String(maryPizoValue) + "," + String(maansiPizoValue) + "," + String(distance));
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
          udp.begin(WiFi.localIP(),udpPort);
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
    }
}
