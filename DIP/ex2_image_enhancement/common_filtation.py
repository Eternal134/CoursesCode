import cv2 as cv
import os
import copy
import numpy as np

from matplotlib import pyplot as plt
from numba import jit

''' 读取并绘制原灰度图像 '''
imgPath = os.path.dirname(__file__) + "\Lena.jpg"
img = cv.imread(imgPath, cv.IMREAD_GRAYSCALE)
plt.subplot(241)
plt.title("origin image")
plt.imshow(img, cmap='gray')

''' 均值低通滤波 '''
img2 = cv.blur(img, (5,5))
plt.subplot(242)
plt.title("Mean Filter")
plt.imshow(img2, cmap='gray')

''' 高斯低通滤波 '''
img3 = cv.GaussianBlur(img, (7, 3), 1)
plt.subplot(243)
plt.title("Gaussian Filter")
plt.imshow(img3, cmap='gray')

''' 增强图像=原图-均值低通滤波 '''
img4 = img*2 - img2
plt.subplot(245)
plt.title("Enhanced By Mean")
plt.imshow(img4, cmap='gray')

''' 增强图像=原图-高斯低通滤波 '''
img5 = img*2 - img3
plt.subplot(246)
plt.title("Enhanced By Gaussian")
plt.imshow(img5, cmap='gray')

''' 'sobel'边缘算子增强 '''
x = cv.Sobel(img, cv.CV_16S, 1, 0)
y = cv.Sobel(img, cv.CV_16S, 0, 1)
absX = cv.convertScaleAbs(x)
absY = cv.convertScaleAbs(y)
img6 = cv.addWeighted(absX, 0.5, absY, 0.5, 0)
plt.subplot(247)
plt.title("soble")
plt.imshow(img6, cmap='gray')

''' 'prewitt'边缘算子增强 '''
# Prewitt算子
kernelx = np.array([[1,1,1],[0,0,0],[-1,-1,-1]],dtype=int)
kernely = np.array([[-1,0,1],[-1,0,1],[-1,0,1]],dtype=int)
x = cv.filter2D(img, cv.CV_16S, kernelx)
y = cv.filter2D(img, cv.CV_16S, kernely)
# 转 uint8 ,图像融合
absX = cv.convertScaleAbs(x)
absY = cv.convertScaleAbs(y)
img7 = cv.addWeighted(absX, 0.5, absY, 0.5, 0)
plt.subplot(248)
plt.title("Prewitt")
plt.imshow(img7, cmap='gray')

plt.show()