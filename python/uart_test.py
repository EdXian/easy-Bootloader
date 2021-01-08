import serial
import time
COMPORT='COM10'
BAUDRATE=115200
ser = serial.Serial("COM10", 115200)
print("Serial: ", ser.isOpen())

rList = [0x55, 0x05, 0x03, 0x5d, 0, 0, 0]
arr = bytes(rList)
try:
    while(True):
         print(bytes(b'your_commands'))
         #ser.write(bytes(b'your_commands'))
         #ser.write(0x55)
         #ser.write(0x05)
         #ser.write(0x03)
         #ser.write(0x5d)
         #ser.write(0x00)
         #ser.write(0x00)
         #ser.write(0x00)
         ser.write(rList)
         time.sleep(1)
             #while ser.in_waiting:
           
            
            #data=ser.read(4)
            #data=ser.readline()
            #data=ser.readAll()
except KeyboardInterrupt:
    print("XXXXXX")
    ser.close()  