from machine import SPI, Pin, I2C
from mpu6050 import init_mpu6050, get_mpu6050_data
import uos
import math
import time
import ujson
import neopixel
import neural_network_controller

i2c = I2C(0, scl=Pin(21), sda=Pin(20), freq=400000)
btn_1 = Pin(9, Pin.IN, Pin.PULL_UP)
btn_2 = Pin(14, Pin.IN, Pin.PULL_UP)
btn_3 = Pin(15, Pin.IN, Pin.PULL_UP)
led = Pin(22, machine.Pin.OUT)

init_mpu6050(i2c)
mode = 0
    
    
pixels = neopixel.NeoPixel(led, 8)
RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0,0,255)

def led_color(i, color):
    pixels[i] = color
    pixels.write()
        
def led_clear(i):
    pixels[i] = (0,0,0)
    pixels.write()

def neural_network(data_pack):
    if int(data_pack[0][3])%6 <=1:
        return 'n'
    if int(data_pack[0][3])%6 ==2:
        return 'l'
    if int(data_pack[0][3])%6 ==3:
        return 's'
    if int(data_pack[0][3])%6 ==4:
        return 'w'
    if int(data_pack[0][3])%6 ==5:
        return 'r'
    
    
    
for i in range(0,8):
    led_clear(i)
                    
while True:
    if not btn_1.value():
        counter = 0
        data_pack = list()
        print("CHECKING STARTED")
        while True:
            current_mpu6050_data = get_mpu6050_data(i2c)
            current_gyro_coordinates = list(current_mpu6050_data.items())[0][1]
            current_gyro_coordinates = list(current_gyro_coordinates.values())
            current_gyro_z = current_gyro_coordinates[0]
            current_gyro_y = current_gyro_coordinates[1]
            current_gyro_x = current_gyro_coordinates[2]
            current_accel_coordinates = list(current_mpu6050_data.items())[1][1]
            current_accel_coordinates = list(current_accel_coordinates.values())
            current_accel_z = current_accel_coordinates[0]
            current_accel_y = current_accel_coordinates[1]
            current_accel_x = current_accel_coordinates[2]
            data_packet = [current_accel_x, current_accel_y, current_accel_z, current_gyro_x, current_gyro_y, current_gyro_z]
            data_pack.extend(data_packet)
            if len(data_pack)==60:
                max_val = max(data_pack)
                min_val = min(data_pack)
                n=0;
                data_packet = list()
                for i in range(10):
                    mini = list()
                    for p in range(6):
                        mini.append((data_pack[n+p]-min_val)/(max_val-min_val))
                    p+=6
                    data_packet.append(mini)
                output = neural_network_controller.workshop_5(data_packet)
                output_numeric = 1
                if output == 'n':
                    output_numeric = 1
                if output == 'l':
                    output_numeric = 2
                if output == 's':
                    output_numeric = 3
                if output == 'w':
                    output_numeric = 4
                if output == 'r':
                    output_numeric = 5
                for i in range(0,8):
                        led_clear(i)
                for i in range(0,output_numeric):
                        led_color(i, RED)
                data_pack.clear()
                
            if not btn_2.value():
                for i in range(0,8):
                        led_clear(i)
                print("CHECKING STOPPED")
                break

       
          



