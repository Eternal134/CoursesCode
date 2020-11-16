from matplotlib import pyplot as plt
from math import pi, sin
import numpy as np

Fs = 200
Ts = 1 / Fs
N = 800
para = -0.9025
x = [sin(2*pi*2*n*Ts) + 0.1*sin(2*pi*50*n*Ts) for n in range(N)]
y = [x[0], x[1]]
[y.append(x[n] + x[n - 2] + para * y[n - 2]) for n in range(2, N)]
t = np.linspace(0, Ts, N)
plt.subplot(311)
plt.plot(t, x, c = 'pink')
plt.subplot(313)
plt.plot(t, y, c = 'pink')
plt.show()