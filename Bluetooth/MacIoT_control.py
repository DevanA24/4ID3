import serial
import time

ser = serial.Serial("COM8",9600)
while True:
    print("ON")
    ser.write("LED_ON\n".encode('utf-8'))
    time.sleep(2)
    print("OFF")
    ser.write("LED_OFF\n".encode('utf-8'))
    time.sleep(2)