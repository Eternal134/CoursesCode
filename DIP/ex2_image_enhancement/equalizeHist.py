import cv2 as cv
import os
import copy
import numpy as np

from matplotlib import pyplot as plt
from numba import jit

''' 读取并绘制原图像 '''
imgPath = os.path.dirname(__file__) + "\Lena.jpg"
imgGray = cv.imread(imgPath, cv.IMREAD_GRAYSCALE)
plt.subplot(311)
plt.title("origin image")
plt.imshow(imgGray, cmap='gray')
''' 直方图均衡化处理 '''
equ = cv.equalizeHist(imgGray)
plt.subplot(313)
plt.title("equalized image")
plt.imshow(equ, cmap='gray')

plt.show()