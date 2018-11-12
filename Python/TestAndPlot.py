import matplotlib.pyplot as plt
import csv
import numpy as np
#import pandas as pd
import serial
import seaborn as sns
import time
import _thread

#Collect data from serial port
s = serial.Serial()
#Imput correct port format machine
s.port = 'COM4'  
s.baud = 9600
s.timeout = 2
s.open()

print("\nPress ENTER to begin collecting data\n")
input()

with s as ser:
    with open('micInput.txt', 'wb') as micInput:
        startTime = time.time()
        print("Data Collection Started")
        print("Press Ctrl+C to Stop")
        print("--------------------")
        try:
            while(True):
                micInput.write(ser.read(1024))
        except KeyboardInterrupt:
            pass
            
            
        stopTime = time.time()
        print("\nData Collection Stopped")
        print("Elapsed time: ", "%.4f" % (stopTime - startTime), "Seconds\n")            

x = []
y = []

with open('micInput.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
##    i = 1
##    maxRead = 0
##    for row in plots:
##        if i < 1000:
##            x.append(i)
##            y.append(int(row[0]))
##            if int(row[0]) > maxRead:
##                maxRead = int(row[0])
##                print(i, ',', row[0])
##        i += 1
    i = 1
    for row in plots:
        x.append(i)
        y.append(int(row[0]))
        i += 1
            
plt.figure(1)
plt.plot(x,y, label='Microphone Output')
plt.title('Microphone Output Over Time')
plt.legend()

transformY = []
print('\nTransform Initiated')
startTime = time.time()
transformY = np.fft.fft(y)
print('Transform Completed')
stopTime = time.time()
print("Elapsed time: ", "%.3f" % (stopTime - startTime), "Seconds\n")

#Throw out first value which is invalid
transformY[0] = 0
plt.figure(2)
plt.plot(x,transformY, label='FFT of Microphone Output')
plt.title('FFT of Microphone Output')
plt.legend()
plt.show()
