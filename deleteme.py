

"""
A simple example of an animated plot
"""
import math
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial



PORT = "/dev/ttyACM0"

fig = plt.figure()
ax = fig.add_subplot(111)
ax.set_ylim(0, 250)
#ax.set_xlim(0, 250)

x = np.arange(0, 2*np.pi, 0.01)        # x-array
line, = ax.plot(x, np.sin(x))

distances = []

# TODO: adjust this based on the time between inputs
distances_max_len = 20

ser = serial.Serial(PORT, 9600)

def reading_to_distance(x):
    return (0.0 if x == 0 else 1000 / math.sqrt(x))

# Adds a new distance reading to the distances array. If 
# the array has more than the distances_max_len, remove 
# its first element.
def add_new_distance(distance):
    distances.append(distance)
    if len(distances) > distances_max_len:
        distances.pop(0)    

# Finds the root mean square of an array.
def rms(arr):
    if len(arr) == 0:
        return None
    return math.sqrt(reduce(lambda a, b: a + b, [x**2 for x in arr]) 
                     / len(arr))
    
def animate(i):
    try:
        time, reading, reading2 = ser.readline().strip().split()
    except ValueError:
        pass
    #print recv.strip()
    reading = int(reading)
    #reading2 = int(reading2)
    ser.flush()
    distance = reading_to_distance(reading)
    add_new_distance(distance)
    #except:
        #num = 0
    print int(distance), int(rms(distances))
    line.set_ydata(rms(distances))  # update the data
    return line,

#Init only required for blitting to give a clean slate.
def init():
    line.set_ydata(np.ma.array(x, mask=True))
    return line,

ani = animation.FuncAnimation(fig, animate, np.arange(1, 200), init_func=init,
    interval=25, blit=True)
plt.show()
