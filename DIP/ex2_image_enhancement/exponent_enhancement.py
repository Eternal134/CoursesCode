import cv2 as cv
import os
import copy
from matplotlib import pyplot as plt
import numpy as np
from numba import jit
import math as m

''' 读取并绘制原图像 '''
imgPath = os.path.dirname(__file__) + "\Lena.jpg"
img = cv.imread(imgPath)
img = cv.cvtColor(img, cv.COLOR_BGR2RGB)
plt.subplot(331)
plt.title("original image")
plt.imshow(img)

@jit
def exponentTransf(img, r):
    ''' 指数变换
        @parm img 原图像
        @parm r 指数变换参数
        @return 变换后的图像
    '''
    # cv.normalize(img, img, 0, 1, cv.NORM_MINMAX)
    imgEnhanced = np.zeros(img.shape)
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            for k in range(img.shape[2]):
                imgEnhanced[i][j][k] = np.power(img[i][j][k], r)
    cv.normalize(imgEnhanced, imgEnhanced, 0, 255, cv.NORM_MINMAX)
    return imgEnhanced

''' r=2 '''
imgEnhanced = np.uint8(exponentTransf(img, 2))
plt.subplot(333)
plt.title("exponent enhancement r=2")
plt.imshow(imgEnhanced)

''' r=1 '''
imgEnhanced = np.uint8(exponentTransf(img, 1))
plt.subplot(337)
plt.title("exponent enhancement r=1")
plt.imshow(imgEnhanced)

''' r=0.5 '''
imgEnhanced = np.uint8(exponentTransf(img, 0.5))
plt.subplot(339)
plt.title("exponent enhancement r=0.5")
plt.imshow(imgEnhanced)
plt.show()