import numpy as np
import matplotlib.pyplot as plt

fs = 5000       # 采样频率
T = 1 / fs      # 采样周期
N = 500         # 采样点个数
A1 = 3          # 第一个正弦函数的振幅
f1 = 80         # 第一个正弦函数的数字频率
t1 = np.linspace(0, (N - 1) * T, N)                     # 自变量取值
y1 = [A1 * np.sin(2 * np.pi * f1 * t) for t in t1]      # 因变量求值
plt.subplot(311)                                        # 分图1
plt.title("sin function1", fontsize = 24)               # 设置标题
plt.xlabel("time/s", fontsize = 14)                     # 设置x轴标签
plt.ylabel("x(t)", fontsize = 14)                       # 设置y轴标签
plt.tick_params(axis = 'both', labelsize = 14)          # 设置刻度标记的大小
plt.plot(t1, y1)                                        

A2 = 10         # 第一个正弦函数的振幅
f2 = 200        # 第一个正弦函数的数字频率
t2 = np.linspace(0, (N - 1) * T, N)
y2 = [A2 * np.sin(2 * np.pi * f2 * t) for t in t2]
plt.subplot(313)
plt.title("sin function2", fontsize = 24)
plt.xlabel("time/s", fontsize = 14)
plt.ylabel("x(t)", fontsize = 14)
plt.tick_params(axis = 'both', labelsize = 14)
plt.plot(t2, y2, color = 'c')
plt.show()