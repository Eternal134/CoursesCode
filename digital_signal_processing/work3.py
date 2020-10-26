# -*- coding:utf-8 -*-
from scipy import signal, fftpack
from matplotlib import pyplot as plt
from math import pi, cos, exp, sin
import numpy as np

# 生成一组10000个满足正态分布的数据
s0 = np.random.randn(10000)
# 模拟带通滤波器设计，返回滤波器的分子(b)和分母(a)多项式
b, a = signal.butter(5, 0.1)
# 滤波函数，根据分子(b)和分母(a)对s0进行滤波
s = signal.filtfilt(b, a, s0)
# 对s0做快速傅里叶变换
S0 = fftpack.fft(s0)
# 对s做快速傅里叶变换
S = fftpack.fft(s)
N = len(s0)
# 对s做频谱搬移
X = fftpack.fftshift(fftpack.fft([(cos(0.6 * n) + cos(0.8 * n)) * i 
                                  for i, n in zip(s, range(N))]))
# 在[0, 2pi)区间内取10000个点
w = np.linspace(0, 2 * pi - 2 * pi / 10000, 10000)
# 绘图
plt.figure(1)
# 原生数据图像
plt.subplot(511)
plt.plot(w, [abs(i) for i in S0], c = 'pink', linewidth = 1)
plt.title("original")
plt.xlabel('w/rad')
# 滤波后的数据图像
plt.subplot(513)
plt.plot(w, [abs(i) for i in S], c = 'pink', linewidth = 1)
plt.title("filtering")
plt.xlabel('w/rad')
# 频谱搬移后的图像
plt.subplot(515)
plt.plot(w, [abs(i) for i in X], c = 'pink', linewidth = 1)
plt.title("spectrum shift")
plt.xlabel('w/rad')
plt.show()