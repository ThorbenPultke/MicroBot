import serial as serial
import time
PORT = 'COM3'
BAUDRATE = 4800
arduino = serial.Serial(port = PORT, baudrate = BAUDRATE, timeout = 1)
time.sleep(1)

def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(1)
    data = arduino.readline()
    return data
    
while True:
    num = input("Enter a number: ") # Taking input from user
    value = write_read(num)
    print(value) # printing the value