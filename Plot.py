import math
import sys
import random
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial


PORT = "/dev/ttyACM0"
ser = serial.Serial(PORT, 9600)

def get_readings():
    return ser.readline().strip().split()

def reading_to_distance(x):
    return (0.0 if x == 0 else 1000 / math.sqrt(x))

class Graph:
    
    def __init__(self):
        self.verbose = True
        self.distances = []
        # TODO: adjust this based on the time between inputs
        self.distances_max_len = 20
        
    # Finds the root mean square of the distances array.
    def rms(self):
        if len(self.distances) == 0:
            return None
        return math.sqrt(reduce(lambda a, b: a + b, \
                                [x**2 for x in self.distances]) \
                     / len(self.distances))
        
    # reading: a string representing a raw input value.
    def add_reading(self, reading):
        reading = int(reading)
        ser.flush()
        distance = reading_to_distance(reading)
        self.add_distance(distance)
        if (self.verbose):
            print int(distance), int(self.rms())

    # Adds a new distance reading to the distances array. If 
    # the array has more than the distances_max_len, remove 
    # its first element.
    def add_distance(self, distance):
        self.distances.append(distance)
        if len(self.distances) > self.distances_max_len:
            self.distances.pop(0)   

    def plot(self):
        # TODO: update the plot rather than repeatedly closing and opening 
        # different plots
        xs = [i for i in range(len(self.distances))]
#        plt.plot(xs, self.distances)
#        plt.show()


graph = Graph()

while True:
    try:
        time, reading, reading2 = get_readings()
        graph.add_reading(reading)
        graph.plot()
    except ValueError as e:
        print "Error: ", str(e)
#    except BaseException as e:
#        print "Error: ", str(e)

