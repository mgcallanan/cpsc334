# Importing Libraries
import serial
from pythonosc import udp_client
import time

ser = serial.Serial(port='/dev/cu.usbserial-14110', baudrate=115200, timeout=.1)

# Set up sending OSC messages to supercollider
sc_client = udp_client.SimpleUDPClient("127.0.0.1", 57120) # Default ip and port for SC


next_line = False
while True:

    data = ser.readline()
    if next_line:
        decoded_line = data[0:len(data)-2].decode("utf-8")
        print(decoded_line)
        
        sc_client.send_message("/rssi", int(decoded_line))
        next_line = False
    if data == b'Last Packet Recv Data:\r\n':
        next_line = True
