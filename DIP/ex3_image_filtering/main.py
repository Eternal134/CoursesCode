import sys
import os
# 获取当前代码文件绝对路径
current_dir = os.path.dirname(os.path.abspath(__file__))
# 将需要导入模块代码文件相对于当前文件目录的绝对路径加入到sys.path中
sys.path.append(os.path.join(current_dir, ".."))

from ex3_image_filtering.image_fliter_factory import ImageFliterFactory
from ex3_image_filtering.SpatialSmoothing import SpatialSmoothing

import numpy as np
import cv2 as cv

import matplotlib.pyplot as plt

# 设置中文字体
plt.rcParams['font.sans-serif'] = 'SimHei'

def readGrayImage(imageName: str) -> np.ndarray:
    """从文件中读取灰度图像

    Args:
        imageName (str): 图像名称

    Returns:
        np.ndarray: 图像矩阵
    """
    imgPath = os.path.dirname(__file__) + "//" + imageName
    return cv.imread(imgPath, cv.IMREAD_GRAYSCALE)

def drawTwoGrayImages(img1: np.ndarray, img2: np.ndarray, title: str, package: str = "") -> None:
    """绘制处理前后灰度图像

    Args:
        img (np.ndarray): 图1
        imgProcessed (np.ndarray): 图2
        title (str): 名称
    """
    fig = plt.figure()
    fig.canvas.set_window_title(title)
    plt.subplot(121)
    plt.title("image1")
    plt.imshow(img1, cmap='gray')
    plt.subplot(122)
    plt.title("image2")
    plt.imshow(img2, cmap='gray')
    packagePath = os.path.dirname(__file__) + "//result//" + package
    # 如果文件夹不存在，则创建
    if not os.path.exists(packagePath):
        os.mkdir(packagePath)
    filePath = packagePath + "//" + title + ".jpg"
    plt.savefig(filePath)
    # plt.show()
    
def spnoise(img: np.ndarray, prob: float) -> np.ndarray:
    """给图像添加椒盐噪声

    Args:
        img (np.ndarray): 原图像
        prob (float): 噪声比例

    Returns:
        np.ndarray: 添加椒盐噪声后的图像
    """
    imgProcessed = np.copy(img)
    threshold = 1 - prob
    with np.nditer(img, flags=['multi_index']) as it:
        while not it.finished:
            
            row, col = it.multi_index
            randomFloat = np.random.rand()
            if randomFloat <= prob:
                imgProcessed[row][col] = 0
            elif randomFloat >= threshold:
                imgProcessed[row][col] = 255
            it.iternext()
    return imgProcessed
            
def lowPassFliter(imgAddedNoise) -> None:
    """低通滤波法

    Args:
        imgAddedNoise (np.ndarray): 待滤波图像
        
    """
    resultPackage = "低通滤波法"
    mask1 = np.full((3, 3), 1/9)
    mask2 = np.full((5, 5), 1/25)
    
    fliter = ImageFliterFactory.lowPassFliterFactory()
    drawTwoGrayImages(imgAddedNoise, fliter.smoothing(imgAddedNoise, mask1), 
                        "3*3低通滤波法处理", resultPackage)
    drawTwoGrayImages(imgAddedNoise, fliter.smoothing(imgAddedNoise, mask2),
                        "5*5低通滤波法处理", resultPackage)
    
    fliter = ImageFliterFactory.medianFliterFactory()
    drawTwoGrayImages(imgAddedNoise, fliter.smoothing(imgAddedNoise, mask1, threshold=64),
                        "3*3超限像素平滑法处理(T=64)", resultPackage)
    drawTwoGrayImages(imgAddedNoise, fliter.smoothing(imgAddedNoise, mask2, threshold=48),
                        "5*5超限像素平滑法处理(T=48)", resultPackage)

def medianFliter(imgAddedNoise: np.ndarray) -> None:
    """中值滤波法"""
    
    mask1 = np.full((3, 3), 1)
    mask2 = np.full((5, 5), 1)
    resultPackage = "中值滤波法"
    
    fliter = ImageFliterFactory.medianFliterFactory()
    drawTwoGrayImages(imgAddedNoise, fliter.smoothing(imgAddedNoise, mask1),
                        "3*3中值滤波平滑处理", package=resultPackage)
    drawTwoGrayImages(imgAddedNoise, fliter.smoothing(imgAddedNoise, mask2),
                        "5*5中值滤波平滑处理", package=resultPackage)

def enhanceImage(img: np.ndarray) -> None:
    """图像增强

    Args:
        imgAddedNoise (np.ndarray): 待处理图像
        
    """
    
    enhancement = ImageFliterFactory.laplacianEnhancementFactory()
    drawTwoGrayImages(img, enhancement.enhanceImage(img), "拉普拉斯算子图像增强", "图像增强")

if __name__ == '__main__':
    
    
    img = readGrayImage("Lena.tiff")
    imgAddedNoise = spnoise(img, 0.02)
    # drawTwoGrayImages(img, imgAddedNoise, "给图像添加椒盐噪声前后")
    
    # medianFliter(imgAddedNoise)
    # lowPassFliter(imgAddedNoise)
    enhanceImage(img)