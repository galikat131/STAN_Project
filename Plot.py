import math
import sys
import random
import numpy as np
import serial
from time import sleep

# first = white
# second = bottom
# third = other

#PORT = "/dev/ttyACM0"
#ser = serial.Serial(PORT, 9600)

class FakeData:

    def __init__(self):
        self.prev_fake_data = 500

    def get(self):
        self.prev_fake_data += random.randrange(-10, 11)
        return self.prev_fake_data

fakes = [FakeData(), FakeData(), FakeData()]

def get_readings():
    global fakes
    return [0] + map(lambda x: x.get(), fakes)
#    return ser.readline().strip().split()

def reading_to_distance(x):
    if (x <= 0):
         return 0.0
    root = math.sqrt(x)
    return 1000/root

class Graph:
    
    def __init__(self):
        self.verbose = False
        self.distances = []
        # TODO: adjust this based on the time between inputs
        self.distances_max_len = 10 # 20
        self.prev_rms = 1
        
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
#        ser.flush()
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

    def delta(self):
        rms = self.rms()
        diff = (rms - self.prev_rms) / self.prev_rms
        self.prev_rms = rms
        return diff
        


graph = Graph()
graph2 = Graph()
graph3 = Graph()

while True:
    try:
        time, reading, reading2, reading3 = get_readings()
        graph.add_reading(reading)
        graph2.add_reading(reading2)
        graph3.add_reading(reading3)
#        print "(%d, %d, %d)" % (graph.delta(), graph2.delta(), graph3.delta()
        print "(%f, %f, %f)" % (graph.delta(), graph2.delta(), graph3.delta())
        sleep(1)
        #graph.plot()
    except ValueError as e:
        print "Error: ", str(e)
#    except BaseException as e:
#        print "Error: ", str(e)

