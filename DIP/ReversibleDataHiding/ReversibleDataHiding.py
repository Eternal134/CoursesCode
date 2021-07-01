import os
from typing import Tuple
import cv2 as cv
import numpy as np

from matplotlib import pyplot as plt

# 设置中文字体
plt.rcParams['font.sans-serif'] = 'SimHei'

def readGrayImage() -> np.ndarray:
    """ 读取灰度图像
        returns:
            img 图像numpy数组
    """
    imgPath = os.path.dirname(__file__) + "\Lena.tiff"
    img = cv.imread(imgPath, cv.IMREAD_GRAYSCALE)
    return img

def getPeakAndZeroPoint(imgGray: np.ndarray) -> Tuple[int, int]:
    """ 获取灰度图像的灰度直方图的峰值点和零值点
        args:
            imgGray 灰度图像的numpy二维数组
        returns:
            peakPoint, zeroPoint    
    """
    # 统计直方图
    hist = cv.calcHist([imgGray], [0], None, [256], [0,256])
    peakPoint = np.where(hist==hist.max())[0][0]
    zeroPoint = np.where(hist==hist.min())[0][-1]
    return peakPoint, zeroPoint

def embedding(imgGray: np.ndarray, bytes: list) -> Tuple[np.ndarray, int]:
    """ 数据嵌入
        args:
            imgGray 灰度图像
            bytes 要嵌入的字节流
        returns:
            imgEmbedded 嵌入数据后的图像
            byteIndex 嵌入数据的字节数
    """
    byteIndex = 0
    imgEmbedded = np.copy(imgGray)
    # 获取图像灰度直方图的峰值点和零值点
    peakPoint, zeroPoint = getPeakAndZeroPoint(imgGray)
    # 两点中较小的作为区间左端点，较大的作为区间右端点
    leftPoint, rightPoint = (peakPoint, zeroPoint) if zeroPoint > peakPoint else (zeroPoint, peakPoint)
    # 使用迭代器迭代数组并修改
    with np.nditer(imgEmbedded, op_flags=['readwrite']) as it:
        for pixel in it:
            if pixel > leftPoint and pixel < rightPoint:
                pixel[...] = pixel + 1
            elif pixel == leftPoint and byteIndex < len(bytes):
                # 如果下一个要嵌入的字节是1，当前像素值+1，否则不变
                pixel[...] = pixel + 1 if bytes[byteIndex] else pixel
                byteIndex += 1
    return imgEmbedded, byteIndex

def extract(imgEmbedded: np.ndarray, bytesNum: int) -> Tuple[np.ndarray, list]:
    """ 数据提取算法
        args:
            imgEmbedded 存在嵌入信息的灰度图像
            bytesNum 要提取的字节个数
        returns:
            imgExtraction 提取数据后的图像
            byteList 提取出来的字节流
    """
    byteList = []
    peakPoint, zeroPoint = getPeakAndZeroPoint(imgEmbedded)
    # 两点中较小的作为区间左端点，较大的作为区间右端点
    leftPoint, rightPoint = (peakPoint, zeroPoint) if zeroPoint > peakPoint else (zeroPoint, peakPoint)

    with np.nditer(imgEmbedded, op_flags=['readwrite']) as it:
        for pixel in it:
            if len(byteList) < bytesNum:
                if pixel == leftPoint - 2:
                    byteList.append(0)
                elif pixel == leftPoint - 1:
                    byteList.append(1)
                    pixel[...] = pixel - 1
            if pixel > leftPoint - 1 and pixel < rightPoint:
                pixel[...] = pixel - 1
    return imgEmbedded, byteList

def showGrayImageAndHist(img: np.ndarray, windowTitle: str) -> None:
    """ 绘制灰度图片及对应直方图
        args：
            img 图像数组
            windowTitle 窗口标题
    """
    fig = plt.figure()
    fig.canvas.set_window_title(windowTitle)
    plt.subplot(311)
    plt.title("灰度图像")
    plt.imshow(img, cmap='gray')
    plt.subplot(313)
    plt.title("灰度直方图")
    plt.hist(img.ravel(), 256, [0, 256])
    plt.show()

def generateRandom01(size: int) -> list:
    """ 生成随机01序列
        args:
            size 序列长度
        returns:
            byteList 序列列表
    """
    return list(np.random.randint(2, size=size))

# 此函数没用
def string2byteList(s:str) -> list:
    """ 将字符串转换成二进制字节流
        args:
            s 字符串
        returns:
            byteList 字符串对应的字节流
    """
    byteList = []
    for byte in bytes(s, encoding="utf-8"):
        # 字符串转字节转二进制数字
        byteList += list(map(lambda x: int(x), list(bin(byte)[2:])))
    return byteList

if __name__ == "__main__":

    imgGray = readGrayImage()
    showGrayImageAndHist(imgGray, "嵌入数据前")
    byteList = generateRandom01(256000)
    imgEmbedded, bytesNum = embedding(imgGray, byteList)
    print("嵌入的字节数：", bytesNum)
    showGrayImageAndHist(imgEmbedded, "嵌入数据后")
    imgExtraciton, byteListExtraction = extract(imgEmbedded, bytesNum)
    showGrayImageAndHist(imgExtraciton, "提取数据后")
    if byteList[:bytesNum] == byteListExtraction:
        print("提取出的数据完全正确！")
    else:
        print("提取出的数据不正确！")