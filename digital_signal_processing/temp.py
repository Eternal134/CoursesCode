import numpy as np
from scipy import fftpack
from matplotlib import pyplot as plt

Fs = 100
N = 200
g = np.random.normal(0, 1, N) 
G = fftpack.fftshift(fftpack.fft(g))
f = np.linspace(- Fs / 2, Fs / 2 - Fs / N, N)
plt.stem(f, abs(G))
plt.show()