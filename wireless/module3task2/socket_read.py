import socket
from pythonosc import udp_client
import math


# Define array indices for esp32 input
MARY_PIZO_IND = 0
MAANSI_PIZO_IND = 1
DISTANCE_IND = 2

# Last 10 RSSI/distance values for denoising
rssi_queue = []
rssi_total = 0

# Set up receiving for ESP32 wifi messages
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  
# Maansi Laptop IP
# s.bind(("172.29.28.52", 8090 )) # Local ip address

# Mary Laptop IP
s.bind(("172.29.16.220", 8092 )) # Local ip address

# Set up sending OSC messages to supercollider
sc_client = udp_client.SimpleUDPClient("127.0.0.1", 57120) # Default ip and port for SC

def denoise_dinstance(curr_dist):
    global rssi_queue
    global rssi_total

    rssi_queue.append(curr_dist)
    rssi_total += curr_dist

    removed_rssi = 0

    if len(rssi_queue) > 10:
        removed_rssi = rssi_queue.pop(0)
        rssi_total -= removed_rssi
    
    denoised_rssi = math.floor(rssi_total / len(rssi_queue))

    return denoised_rssi
    
 
while True:
    # Receive data string of sensor values
    data, addr = s.recvfrom(1024)
    data_arr = data.decode("ASCII").split(',')
    # print(data_arr)
    
    # Extract int values from string array
    mary_pizo = int(data_arr[MARY_PIZO_IND])
    maansi_pizo = int(data_arr[MAANSI_PIZO_IND])
    distance = denoise_dinstance(int(data_arr[DISTANCE_IND]))
    print(mary_pizo, maansi_pizo, distance)

    # Send OSC message to supercollider
    sc_client.send_message("/print", distance)