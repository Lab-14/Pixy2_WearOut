import time
import serial
import numpy as np
import base64


def get_byte_array(size):
    # decide array size (key = size in KB)
    array_size = {
        1: (800, 1200),
        2: (800, 1100),
        3: (900, 900),
        4: (800, 900),
        5: (800, 800),
        6: (800, 700),
        7: (800, 600),
        8: (600, 600),
        9: (512, 512),
        10: (440, 440),
        11: (360, 360),
        12: (224, 224),
        13: (160, 160),
        14: (96, 96),
        15: (70, 70)
    }

    # np.random.seed(10)
    random_data = np.random.randint(low=10, high=250, size=array_size[size], dtype=np.uint8)
    return random_data
    # print(random_data)

   # b_array = bytearray(random_data)
    # print(b_array)

    #return b_array
# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='com5',
    # '/dev/ttyUSB1',
    baudrate=921600,
    parity='N',
    stopbits=1,
    bytesize=8
)

for data_size in range(15,16): # in bytes
	print(data_size)
	array = get_byte_array(data_size)

	start_time = time.time()
	print (start_time)
	for line_array in array:
		# print(array[0])
		line = ''	
		for l in line_array:
			line+=chr(l)
			#line+=chr(l)
		#print(line)
		# ser.isOpen()

		# print 'Enter your commands below.\r\nInsert "exit" to leave the application.'

		# ser = serial.Serial(0)  # open first serial port
		# print (ser.portstr)       # check which port was really used
		#ser.write(b'hello')       # write a string
		# print(base64.b64encode(line.encode()))
		#ser.write(base64.b64encode(line.encode()))
		ser.write(line.encode())
	print (time.time()-start_time)
	time.sleep(5)

	print ("Doing two iterations over same resolution")

	start_time = time.time()
	print (start_time)
	for line_array in array:
		# print(array[0])
		line = ''	
		for l in line_array:
			line+=chr(l)
		ser.write(line.encode())
	print (time.time()-start_time)
	time.sleep(5)


ser.close()               # close port
