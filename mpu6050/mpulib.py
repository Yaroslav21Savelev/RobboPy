import signal
import time
from mpu6050 import mpu6050

sensor = mpu6050(0x68)


def handler(signum, frame):
    gyro_data = sensor.get_gyro_data()
    global angle
    angle = (angle + (gyro_data['z']+0.67)*0.02)
    #angle = gyro_data['z'] + 0.67

angle = 0
signal.signal(signal.SIGALRM, handler)

init = time.time()

signal.setitimer(signal.ITIMER_REAL, 1, 0.02)

start = time.time()

while (time.time() - start) < 100:
    time.sleep(0.1)
    print(angle)

signal.setitimer(signal.ITIMER_REAL, 0) 
