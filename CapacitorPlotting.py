

"""
A simple example of an animated plot
"""
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial



PORT = "/dev/ttyACM2"

fig = plt.figure()
ax = fig.add_subplot(111)
ax.set_ylim(0, 200)

x = np.arange(0, 2*np.pi, 0.01)        # x-array
line, = ax.plot(x, np.sin(x))

ser = serial.Serial(PORT)

def animate(i):
    #try:
    recv = ser.readline().strip()
    #print recv.strip()
    num = int(ser.readline())
    ser.flush()
    print num
    #except:
        #num = 0
    line.set_ydata(num)  # update the data
    return line,

#Init only required for blitting to give a clean slate.
def init():
    line.set_ydata(np.ma.array(x, mask=True))
    return line,

ani = animation.FuncAnimation(fig, animate, np.arange(1, 200), init_func=init,
    interval=25, blit=True)
plt.show()
