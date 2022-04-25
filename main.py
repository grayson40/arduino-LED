# Importing Libraries
import serial
import time

arduino = serial.Serial(port='COM10', baudrate=115200, timeout=.1)


def write_to_serial(data):
    arduino.write(bytes(data, 'utf-8'))
    time.sleep(0.05)
    print(f'\n\tWrote "{data}" to COM8\n')


while True:
    print('LED Patterns:\n\n1.) Color Wipe\n2.) Rainbow\n3.) Theater Chase\n4.) Stripes\n5.) Cylon\n')
    data = input(">> ")  # Taking input from user
    write_to_serial(data)
