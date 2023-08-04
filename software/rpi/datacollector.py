from machine import SPI, Pin, I2C
from mpu6050 import init_mpu6050, get_mpu6050_data
import uos
import math
import time
import ujson
import neopixel

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


for i in range(0,8):
    led_clear(i)
                    
while True:
    counter =0
    flag = False
    if not btn_3.value():
        if mode>=4:
            mode = 0
            for i in range(0,8):
                led_clear(i)
        else:
            mode +=1
            led_color(mode, BLUE)
        print(mode)
        time.sleep(2)
        continue
    if not btn_1.value():
        nowtime = time.localtime()
        line_counter = 0
        filename = str(mode) +'_'+ str(nowtime[3])+'_'+ str(nowtime[4])+'_'+ str(nowtime[5])+'_'+ str(nowtime[2])+'_'+str(nowtime[1])
        print("RECORDING STARTED")
        with open(filename+'.bin', 'ab') as f:
            while True:
                if not flag:
                    led_color(counter, RED)
                else:
                    led_clear(counter)
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
                if(line_counter!=9):
                    str_raw = str(math.floor(current_gyro_z))+" "+str(math.floor(current_gyro_y))+" "+str(math.floor(current_gyro_x))+" "+str(math.floor(current_accel_z))+" "+str(math.floor(current_accel_y))+" "+str(math.floor(current_accel_x))+" "
                    line_counter +=1
                else:
                    str_raw = str(math.floor(current_gyro_z))+" "+str(math.floor(current_gyro_y))+" "+str(math.floor(current_gyro_x))+" "+str(math.floor(current_accel_z))+" "+str(math.floor(current_accel_y))+" "+str(math.floor(current_accel_x))+"\n"
                    line_counter =0
               #print(current_accel_z)
                f.write((str_raw))
                if counter == 7:
                    counter = 0
                    flag = not flag
                else:
                    counter+=1
                if not btn_2.value():
                    print("RECORDING STOPPED")
                    f.close()
                    for i in range(0,8):
                        time.sleep(0.1)
                        led_color(i, GREEN)
                    time.sleep(1)
                    for i in range(0,8):
                        led_clear(i)
                    break

       
          

