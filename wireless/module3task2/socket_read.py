import socket
from pythonosc import udp_client

# Define array indices for esp32 input
MARY_PIZO_IND = 0
MAANSI_PIZO_IND = 1
DISTANCE_IND = 2

# Set up receiving for ESP32 wifi messages
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  
s.bind(("172.29.28.52", 8090 )) # Local ip address

# Set up sending OSC messages to supercollider
sc_client = udp_client.SimpleUDPClient("127.0.0.1", 57120) # Default ip and port for SC
 
while True:
    # Receive data string of sensor values
    data, addr = s.recvfrom(1024)
    data_arr = data.decode("ASCII").split(',')
    print(data_arr)
    
    # Extract int values from string array
    mary_pizo = int(data_arr[MARY_PIZO_IND])
    maansi_pizo = int(data_arr[MAANSI_PIZO_IND])
    distance = int(data_arr[DISTANCE_IND])

    # Send OSC message to supercollider
    sc_client.send_message("/print", distance)