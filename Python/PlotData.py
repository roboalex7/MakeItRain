import matplotlib.pyplot as plt
import csv
import numpy as np

x = []
y = []

t = []

with open('microphone.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    i = 1
    maxRead = 0
    for row in plots:
        if i < 1000:
            x.append(i)
            y.append(int(row[0]))
            if int(row[0]) > maxRead:
                maxRead = int(row[0])
                print(i, ',', row[0])
        i += 1
            
plt.figure(1)
plt.plot(x,y, label='Microphone Output')
plt.title('Microphone Output Over Time')
plt.legend()

transformY = []
print('Transform Initiated')
transformY = np.fft.fft(y)
print('Transform Completed')
for j in range(0,99):
    if transformY[j] > 50000:
        transformY[j] = 0
plt.figure(2)
plt.plot(x,transformY, label='FFT of Microphone Output')
plt.title('FFT of Microphone Output')
plt.legend()
plt.show()
