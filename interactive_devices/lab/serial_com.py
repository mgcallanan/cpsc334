import serial, sys
port = '/dev/ttyUSB0'
baudrate = 115200
ser = serial.Serial(port,baudrate,timeout=0.001)
while True:
    data = ser.read(1)
    data+= ser.read(ser.inWaiting())
    sys.stdout.write(data.decode('utf-8'))
    sys.stdout.flush()