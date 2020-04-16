#!/usr/bin/python3


import sys, time

sys.path.append("..")

from arduino.usbdevice import ArduinoUsbDevice

try:
    theDevice = ArduinoUsbDevice(idVendor=0x16c0, idProduct=0x05df)
except:
    sys.exit("No DigiUSB Device Found")





if len(sys.argv) == 1:
    print("""Usage:
    usbreset  <cmd>

    cmd:  reset2 or reset0
    """)
    sys.exit()

cmd = sys.argv[1]

def read():
    ret_val = ""
    while True:
        try:
            char = chr(theDevice.read())
            ret_val = ret_val + char
            if char == '\n':
                return "Echo: " + ret_val
        except:
            return ""
print(read())
print(read())
if cmd == "reset2":
    for char in "reset2\n":
        theDevice.write(ord(char))
    print( "Sending cmd: %s\n" %(cmd))
time.sleep(2)
print(read())
print(read())
print(read())
print(read())
