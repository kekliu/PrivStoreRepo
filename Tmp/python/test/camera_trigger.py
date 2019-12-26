# /usr/bin/env python3
# import math
#
# x = 0.0122601
# y = 0.0163688
# z = 0.00076067
# w = 0.999791
# roll = math.atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y))
# pitch = math.asin(2 * (w * y - z * x))
# yaw = math.atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z))
# print(roll, pitch, yaw)


import time

import serial

# print(os.readlink('/dev/trolley_sensors/camera_mode_switcher'))

port = serial.Serial(port='/dev/trolley_sensors/camera_controller', baudrate=9600, bytesize=8, parity='N',
                     stopbits=1, timeout=5)

# port.write([0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x34])
while True:
    port.write([0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30])
    time.sleep(1)
    print(port.read_all())
