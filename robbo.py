import serial
import time
LEFT_WHEEL = 0  #defining constants
RIGHT_WHEEL = 1
FORWARD = 0
BACK = 1

PAD_1 = 1
PAD_2 = 2
PAD_3 = 3
PAD_4 = 4
PAD_5 = 5

FLASH_ON = 1
FLASH_OFF = 0
try:
    port = serial.Serial("/dev/ttyUSB0", baudrate = 57600, timeout = 0.0) #defining port
except serial.serialutil.SerialException:
    try:
        port = serial.Serial("/dev/ttyUSB1", baudrate = 57600, timeout = 0.0)
    except serial.serialutil.SerialException:
        try:
            port = serial.Serial("/dev/ttyUSB2", baudrate = 57600, timeout = 0.0)
        except serial.serialutil.SerialException:
            try:
                port = serial.Serial("/dev/ttyUSB3", baudrate = 57600, timeout = 0.0)
            except serial.serialutil.SerialException:
                port = serial.Serial("/dev/serial0", baudrate = 57600, timeout = 0.0)
def uart(string):
    port.write(string.encode()) #function for sending signals via uart protocol
def motor(motorNumber, motorDirection, speed): # working with built-in engines 
    if motorNumber == 0:
        if motorDirection == 0:
            motorChar = 'a'
        elif motorDirection == 1:
            motorChar = 'b'
    elif motorNumber == 1:
        if motorDirection == 0:
            motorChar = 'c'
        elif motorDirection == 1:
            motorChar = 'd'
            
    uart(motorChar + str(speed) + "\n") # sending data via uart protocol
    
def flash(pad, state):      #working with flashlight
    uart(str(state) + str(pad) + "\n")

def dPadRead(pad):          #getting data from any digital sensor
    uart('2' + str(pad) + "\n")
    time.sleep(0.1)
    while True:
        rcv = repr(port.read(port.inWaiting())) #reading data via uart protocol
        if rcv[2] != "'":
            i = 2
            stroke = ""
            while rcv[i] != "'":
                stroke = stroke + rcv[i]
                i = i + 1
            return int(stroke)
def aPadRead(pad):
    uart('6'+ str(pad) + "\n") #working with analog mode of line sensor
    time.sleep(0.1)
    while True:
        rcv = repr(port.read(port.inWaiting())) #getting data via uart protocol
        if rcv[2] != "'":
            i = 2
            stroke = ""
            while rcv[i] != "'":
                stroke = stroke + rcv[i]
                i = i + 1
            return int(stroke)
def ultrasonic(pad):       #getting data from ultrasonic sensor
    uart('3' + str(pad) + "\n")
    time.sleep(0.1)
    while True:
        rcv = repr(port.read(port.inWaiting())) #reading data via uart protocol
        if rcv[2] != "'":
            i = 2
            stroke = ""
            while rcv[i] != "'":
                stroke = stroke + rcv[i]
                i = i + 1
            return int(stroke)
def sharp(pad):           #getting data from infrared distance sensor
    uart('4' + str(pad) + "\n")
    time.sleep(0.1)
    while True:
        rcv = repr(port.read(port.inWaiting())) #reading data via uart protocol
        if rcv[2] != "'":
            i = 2
            stroke = ""
            while rcv[i] != "'":
                stroke = stroke + rcv[i]
                i = i + 1
            return int(stroke)
def distance(pad):        #getting data from standart dictance sensor
    uart('5' + str(pad) + "\n")
    time.sleep(0.1)
    while True:
        rcv = repr(port.read(port.inWaiting())) #reading data via uart protocol
        if rcv[2] != "'":
            i = 2
            stroke = ""
            while rcv[i] != "'":
                stroke = stroke + rcv[i]
                i = i + 1
            return int(stroke)
    
