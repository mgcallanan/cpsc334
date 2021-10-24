#include "WiFi.h"

// Local IP address for computer
const uint16_t port = 8090;
const char * host = "192.168.1.111"; 

void setup(){
  Serial.begin(115200);

  // Set up wifi connection
  WiFi.mode(WIFI_MODE_STA);
  delay(10);
  WiFi.begin("network_name", "network_password");
  
  Serial.println("Connecting.");
  while(WiFi.status() != WL_CONNECTED) {
      Serial.println(".");
      delay(500);
  }
  
  Serial.println("WiFi connected - IP address: ");
  Serial.println(WiFi.localIP());
  delay(500);
  
  // TODO: Configure input pins
}

void loop(){
  // TODO: replace with real sensor data
  int lightReading = random(5);
  Serial.println(lightReading);

  
  WiFiClient client;

  // Make sure we're connected to wifi
  if (!client.connect(host, port)) {
      Serial.println("Connection to host failed");
      delay(1000);
      return;
  }

  // Send sensor value over wifi
  client.print(lightReading);
  client.stop();
  
  delay(100);

}
