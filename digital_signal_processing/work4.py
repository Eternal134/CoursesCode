import numpy as np
from scipy import fftpack
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import axes3d
from math import sin, pi, cos

def MyDft(x, w):
    ''' 求傅里叶变换中的X(e^(jw)) '''
    Xw = complex(0, 0)
    for n in range(x.size):
        Xw += x[n] * np.exp(complex(0, - w * n))
    return Xw

def MyFftshift(X):
    ''' 自己实现的fftshift函数
        将傅里叶变换结果X的零频点移到频谱的中间 '''
    half_size = X.size // 2
    for i in range(half_size // 2):
        X[i], X[half_size - i - 1] = X[half_size - i - 1], X[i]
        X[i + half_size], X[X.size - i - 1] = X[X.size - i - 1], X[i + half_size]
    return X

Fs = 100            # 采样频率
Ts = 1 / Fs         # 采样周期
N = 400             # 采样点个数
# 时域信号的表达式
fun = lambda n: 2*sin(2*pi*2*n*Ts) + 1.5*sin(2*pi*10*n*Ts) + 0.7*sin(2*pi*15*n*Ts)
# 对时域信号进行采样
x = np.array([fun(n) for n in range(N)])
# 对采样点增加高斯噪声
x += np.random.normal(0, 1, N)
# 做傅里叶变换，并把零频点移到横坐标轴中间
X = fftpack.fftshift(fftpack.fft(x))
# X = fftpack.fft(x)
# 绘图的横坐标
f = np.linspace(-1 * Fs / 2, Fs / 2 - Fs / N, N)
# 测试自己的傅里叶变换函数
my_X = np.array([], dtype = complex)
# 傅里叶变换的频率范围是0~2pi,在这中间取N个点
ws = np.linspace(0, 2 * pi, N, endpoint = False)
for w in ws:
    # 对每个频率求傅里叶变换
    my_X = np.append(my_X, MyDft(x, w))
# 因为做傅里叶变换选择的频率范围是0~2pi，所以需要一个移零频点的操作
# 如果频率范围选择-pi~pi，则不需要这样的操作
my_X = MyFftshift(my_X)
# 时域信号绘图的横坐标
t = np.linspace(0, (N - 1)*Ts, N)

plt.figure(dpi = 150)
plt.subplot(511)
plt.plot(t, x, c = 'pink', linewidth = 1)
plt.xlabel('time/s')
plt.subplot(513)
plt.stem(f, abs(my_X), linefmt = 'y--', markerfmt = 'c')
plt.title('My DFT')
plt.ylabel('Magnitude')
plt.subplot(515)
plt.stem(f, abs(X), linefmt = 'y--', markerfmt = 'c')
plt.title('standard FFT')
plt.xlabel('Frequency/HZ')
plt.ylabel('Magnitude')
# plt.show()

''' 在三维坐标系中绘制x和x的3个正弦分量 '''
x1 = np.array([2*sin(2*pi*2*n*Ts) for n in range(N)])
x2 = np.array([1.5*sin(2*pi*10*n*Ts) for n in range(N)])
x3 = np.array([0.7*sin(2*pi*15*n*Ts) for n in range(N)])
fig = plt.figure(dpi = 200)
ax = fig.gca(projection = '3d')
ax.set_xlabel('frquency/rad')
ax.set_ylabel('time/s')
ax.set_zlabel('scope')
figure1 = ax.plot(np.full((N, ), 0), t, x, c = 'black', linewidth = 1)
figure2 = ax.plot(np.full((N, ), 4*pi*Ts), t, x1, c = 'blue', linewidth = 1)
figure3 = ax.plot(np.full((N, ), 20*pi*Ts), t, x2, c = 'red', linewidth = 1)
figure4 = ax.plot(np.full((N, ), 30*pi*Ts), t, x3, c = 'pink', linewidth = 1)
ax.grid()
plt.show()