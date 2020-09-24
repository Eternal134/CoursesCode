import numpy as np
import matplotlib.pyplot as plt

f0 = 4              # 模拟信号频率
fs = 200            # 采样频率
T = 1 / fs          # 采样周期
a = -0.95           # 滤波参数
N = 200             # 采样个数
t = np.linspace(0, (N - 1) * T, N)                  # 采样时间分量
x = [np.sin(np.pi * 2 * f0 * n) for n in t]         # 采样的幅度
gauss_errors = 0.1 * np.random.normal(0, 1, N)      # 高斯误差
for i in range(len(x)):
    # 在x上加上高斯误差
    x[i] += gauss_errors[i]
y = [x[0]]          # 滤波后的结果，首元素设为x[0]，方便迭代法求差分方程
for n in range(1, N):
    # 迭代法求解差分方程
    y.append(x[n] - a * y[n - 1])

plt.subplot(311)
plt.plot(t, x)
plt.xlabel('time / s')

plt.subplot(313)
plt.plot(t, y)
plt.xlabel('time / s')
plt.show()