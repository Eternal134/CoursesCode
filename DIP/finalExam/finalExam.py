import os
import cv2 as cv
import numpy as np

from matplotlib import pyplot as plt
# 设置中文字体
plt.rcParams['font.sans-serif'] = 'SimHei'

imgPath = os.path.dirname(__file__) + "\Lena.tiff"
img = cv.imread(imgPath, cv.IMREAD_GRAYSCALE)
# 原图
plt.subplot(211)
plt.title("原始图像")
plt.imshow(img, cmap='gray')
hist = cv.calcHist([img], [0], None, [256], [0,256])
# 灰度直方图
plt.subplot(212)
plt.hist(img.ravel(), 256, [0, 256])
plt.show()
# 均衡化后的图像
equ = cv.equalizeHist(img)
plt.subplot(211)
plt.title("直方图均衡化后图像")
plt.imshow(equ, cmap='gray')
hist = cv.calcHist([equ], [0], None, [256], [0,256])
# 灰度直方图均衡化
plt.subplot(212)
plt.hist(equ.ravel(), 256, [0, 256])
plt.show()