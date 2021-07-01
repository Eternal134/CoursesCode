import cv2 as cv
import os
import copy
from matplotlib import pyplot as plt
import numpy as np
from numba import jit

''' 读取并绘制原图像 '''
imgPath = os.path.dirname(__file__) + "\Lena.jpg"
img = cv.imread(imgPath)
img = cv.cvtColor(img, cv.COLOR_BGR2RGB)
plt.subplot(331)
plt.title("original image")
plt.imshow(img)

@jit
def logTransf(img, v):
    ''' log变换
        @parm img 原图像
        @parm v log变换参数
        @return 变换后的图像
    '''
    imgEnhanced = np.zeros(img.shape)
    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            for k in range(img.shape[2]):
                imgEnhanced[i][j][k] = np.log(img[i][j][k]*v + 1) / np.log(v+1)
    return imgEnhanced

''' v=1 '''
imgEnhanced = np.uint8(logTransf(img, 1))
cv.normalize(imgEnhanced, imgEnhanced, 0, 255, cv.NORM_MINMAX)
plt.subplot(333)
plt.title("log enhancement v=1")
plt.imshow(imgEnhanced)

''' v=10 '''
imgEnhanced = np.uint8(logTransf(img, 10))
cv.normalize(imgEnhanced, imgEnhanced, 0, 255, cv.NORM_MINMAX)
plt.subplot(337)
plt.title("log enhancement v=10")
plt.imshow(imgEnhanced)

''' v=100 '''
imgEnhanced = np.uint8(logTransf(img, 100))
cv.normalize(imgEnhanced, imgEnhanced, 0, 255, cv.NORM_MINMAX)
plt.subplot(339)
plt.title("log enhancement v=100")
plt.imshow(imgEnhanced)
plt.show()