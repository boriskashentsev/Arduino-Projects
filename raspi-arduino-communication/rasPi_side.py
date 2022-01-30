import serial
import random
import time

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 19200, timeout=1)
    ser.reset_input_buffer()
    
    while True:
        led_number = random.randint(0,3)
        print("switching led", led_number)
        ser.write(str(led_number).encode('utf-8'))
        time.sleep(1)