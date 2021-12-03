#include <Stepper.h>
#include <ESP32Servo.h>
#include <esp_now.h>
#include <WiFi.h>
#include <WiFiudp.h>

// Set the channel for ESP Now
#define MOTOR_CHANNEL 0

// FOR STEPPER 1
#define A1 25
#define B1 26
#define C1 27
#define D1 14

// FOR STEPPER 2
#define A2 17
#define B2 5
#define C2 18
#define D2 19

// FOR STEPPER 3
#define A3 32
#define B3 15
#define C3 4
#define D3 16
 
#define NUMBER_OF_STEPS_PER_REV 2048 // change this to fit the number of steps per revolution

Stepper myStepper1(NUMBER_OF_STEPS_PER_REV, A1, C1, B1, D1); 
Stepper myStepper2(NUMBER_OF_STEPS_PER_REV, A2, C2, B2, D2);
Stepper myStepper3(NUMBER_OF_STEPS_PER_REV, A3, C3, B3, D3);

// // For UDP messaging
// const char * networkName = "Stairwell_1";
// const char * networkPswd = "Stairwell_1_Password";

// // Laptop IP
// const char * laptopudpAddress = "169.254.6.236";
// const int laptopudpPort = 8090;

// //Are we currently connected?
// boolean connected = false;

// //The udp library class
// WiFiUDP udp;

// byte command[27] = {0x20, 0x00, 0x00, 0x00, 0x16, 0x02, 0x62, 0x3A, 0xD5, 0xED, 0xA3, 0x01, 0xAE, 0x08, 0x2D, 0x46, 0x61, 0x41, 0xA7, 0xF6, 0xDC, 0xAF, 0xD3, 0xE6, 0x00, 0x00, 0x1E};



// Initialize ESP Now with fallback
void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }
}

// Configure AP SSID
void configDeviceAP() {
  const char *SSID = "Motor_1";
  bool result = WiFi.softAP(SSID, "Motor_1_Password", MOTOR_CHANNEL, 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
  }
}

// Callback when data is received from Master
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Recv from: "); Serial.println(macStr);
  Serial.println("Last Packet Recv Data:"); Serial.println(*data);
  Serial.println(WiFi.RSSI());
  Serial.println("");
  
  //Send a packet to laptop with distance and piezo values
  // udp.beginPacket(laptopudpAddress,laptopudpPort);
  // udp.print(String(WiFi.RSSI()));
  // udp.endPacket();
  // Serial.println("Sent UDP Message");
}

void setup(){
  
  // FOR STEPPER
  // set the speed at 5 rpm
//  myStepper1.setSpeed(20);
//  myStepper2.setSpeed(20);
  myStepper3.setSpeed(20);

  
  Serial.begin(115200);

  // For WiFi
  //Set device in AP mode to begin with
  WiFi.mode(WIFI_AP);
  // configure device AP mode
  configDeviceAP();
  // This is the mac address of the Slave in AP Mode
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());

  // // Set up WiFi as station connected to Stairwell Head
  // WiFi.begin(networkName, networkPswd);

  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.println("Connecting to WiFi..");
  // }
 
  // Serial.print("ESP32 IP as soft AP: ");
  // Serial.println(WiFi.softAPIP());
 
  // Serial.print("ESP32 IP on the WiFi network: ");
  // Serial.println(WiFi.localIP());
  
  // Initialize ESPNow with a fallback logic
  InitESPNow();
  
  // Once ESPNow is successfully initialized, we will register for recv CB to
  // get recv packer info.
  esp_now_register_recv_cb(OnDataRecv);


}


void loop(){

  int x = 5;

  //DELETE
  Serial.println("Last Packet Recv Data:"); Serial.println(random(50, 1000));

  // Spin the stepper motor x * 360 deg
  for (int i = 0; i < NUMBER_OF_STEPS_PER_REV * x; i++) {
    //myStepper1.step(1);
    //myStepper2.step(1);
    myStepper3.step(-1);
  }

}
