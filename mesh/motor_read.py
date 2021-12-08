# Importing Libraries
import serial
from pythonosc import udp_client
import time

ser = serial.Serial(port='/dev/cu.usbserial-14210', baudrate=115200, timeout=.1)

# Set up sending OSC messages to supercollider
sc_client = udp_client.SimpleUDPClient("127.0.0.1", 57120) # Default ip and port for SC

def translate(value, leftMin, leftMax, rightMin, rightMax):
    # Figure out how 'wide' each range is
    leftSpan = leftMax - leftMin
    rightSpan = rightMax - rightMin

    # Convert the left range into a 0-1 range (float)
    valueScaled = float(value - leftMin) / float(leftSpan)

    # Convert the 0-1 range into a value in the right range.
    return rightMin + (valueScaled * rightSpan)

next_line = False
while True:

    data = ser.readline()
    if next_line:
        decoded_line = data[0:len(data)-2].decode("utf-8")
        print(decoded_line)
        mapped_rssi = translate(int(decoded_line), 40, 100, 50, 500)

        sc_client.send_message("/rssi", int(mapped_rssi))
        next_line = False
    if data == b'Last Packet Recv Data:\r\n':
        next_line = True
