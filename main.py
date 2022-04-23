# Importing Libraries
import serial
import time
arduino = serial.Serial(port='COM8', baudrate=115200, timeout=.1)


def write_read(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    data = arduino.readline()
    return data


while True:
    print('LED Patterns:\n\n1.) Color Wipe\n2.) Rainbow\n3.) Theater Chase\n4.) Stripes\n5.) Cylon\n')
    num = input(">> ")  # Taking input from user
    value = write_read(num)
