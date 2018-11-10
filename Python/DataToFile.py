import numpy as np
import pandas as pd
from matplotlib import pyplot as plt
import serial
import seaborn as sns

#matplotlib inline

s = serial.Serial()
s.port = 'COM4'
s.baud = 9600
s.timeout = 2
s.open()

switch = True

with s as ser:
    with open('microphone.txt', 'ab') as microphone:
        while(switch):
            microphone.write(ser.read(1024))
