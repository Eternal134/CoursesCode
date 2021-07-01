import cv2 as cv
import os
import copy
from matplotlib import pyplot as plt
import numpy as np
from numba import jit

imgPath = os.path.dirname(__file__) + "\Lena.jpg"
imgGray = cv.imread(imgPath, cv.IMREAD_GRAYSCALE)
plt.subplot(311)
plt.title("origin image")
plt.imshow(imgGray, cmap='gray')

@jit
def threshold_dispose(imgGray, threshold):
    ''' 对灰度图像imgGray做阈值处理 '''
    imgRes = np.zeros(imgGray.shape)
    for i in range(imgGray.shape[0]):
        for j in range(imgGray.shape[1]):
            if imgGray[i][j] > threshold:
                imgRes[i][j] = 255
            else:
                imgRes[i][j] = 0
    return imgRes

imgRes = threshold_dispose(imgGray, 200)
plt.subplot(313)
plt.imshow(imgRes, cmap='gray')
plt.title("threshold dispose")
plt.show()