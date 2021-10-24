import socket
from pythonosc import udp_client

# Set up receiving for ESP32 wifi messages
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
s.bind(("192.168.1.111", 8090 )) # Local ip address
s.listen(0)

# Set up sending OSC messages to supercollider
sc_client = udp_client.SimpleUDPClient("127.0.0.1", 57120) # Default ip and port for SC
 
# Receive data from ESP and transmit to SC
while True:
    esp_client, _ = s.accept()
 
    while True:
        # Get content from ESP32
        content = esp_client.recv(2048)
 
        if len(content) == 0:
           break
        else:
            print(content)
            # Decode message into integer
            num = int(str(content, 'utf8'))
            print(num)
            sc_client.send_message("/print", num)
 
    esp_client.close()