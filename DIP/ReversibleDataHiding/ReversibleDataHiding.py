import os
from typing import Tuple
import cv2 as cv
import numpy as np

from matplotlib import pyplot as plt

# 设置中文字体
plt.rcParams['font.sans-serif'] = 'SimHei'
# 控制是否需要作图
global draw
draw = False

def readGrayImage() -> np.ndarray:
    """ 读取灰度图像
        returns:
            img 图像numpy数组
    """
    imgPath = os.path.dirname(__file__) + "//Lena.tiff"
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
    # hist = cv.calcHist([imgGray], [0], None, [256], [0,256])
    hist, bins = np.histogram(imgGray.ravel(), 256, [0, 256])
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
    if not draw:
        return
    fig = plt.figure()
    fig.canvas.set_window_title(windowTitle)
    plt.subplot(311)
    plt.title("original")
    plt.imshow(img, cmap='gray')
    plt.subplot(313)
    plt.title("histogram")
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

def halfDiamondPredict(img: np.ndarray, oddStart=True) -> np.ndarray:
    """菱形预测一半图像，间隔一个像素预测一个

    Args:
        img (np.ndarray): 图像二维数组
        oddStart (boolean) : 是否从奇数位置开始

    Returns:
        np.ndarray: 菱形预测出的图像的差值直方图
    """
    imgCopy = np.copy(img)
    img = img.astype(np.uint16)
    rowCount, colCount = img.shape
    with np.nditer(img, op_flags=['readwrite'], flags=['multi_index']) as it:
        if not oddStart: it.iternext()
        while not it.finished:
            indexX, indexY = it.multi_index
            if indexX == 0 and indexY == 0:
                # 左上角
                imgCopy[indexX][indexY] = (img[indexX + 1][indexY] + img[indexX][indexY + 1]) // 2
            elif indexX == 0 and indexY == colCount - 1:
                # 右上角
                imgCopy[indexX][indexY] = (img[indexX + 1][indexY] + img[indexX][indexY - 1]) // 2
            elif indexX == rowCount - 1 and indexY == 0:
                # 左下角
                imgCopy[indexX][indexY] = (img[indexX - 1][indexY] + img[indexX][indexY + 1]) // 2
            elif indexX == rowCount - 1 and indexY == colCount - 1:
                # 右下角
                imgCopy[indexX][indexY] = (img[indexX - 1][indexY] + img[indexX][indexY - 1]) // 2
            elif indexX == 0:
                # 第一排，非角
                imgCopy[indexX][indexY] = (img[indexX][indexY - 1] + img[indexX][indexY + 1] + img[indexX + 1][indexY]) // 3
            elif indexY == 0:
                # 第一列，非角
                imgCopy[indexX][indexY] = (img[indexX - 1][indexY] + img[indexX + 1][indexY] + img[indexX][indexY + 1]) // 3
            elif indexX == rowCount - 1:
                # 最下一排，非角
                imgCopy[indexX][indexY] = (img[indexX][indexY + 1] + img[indexX - 1][indexY] + img[indexX][indexY - 1]) // 3
            elif indexY == colCount - 1:
                # 最右一列，非角
                imgCopy[indexX][indexY] = (img[indexX - 1][indexY] + img[indexX + 1][indexY] + img[indexX][indexY - 1]) // 3
            else:
                # 非边缘
                imgCopy[indexX][indexY] = (img[indexX - 1][indexY] + img[indexX + 1][indexY] + 
                                           img[indexX][indexY - 1] + img[indexX][indexY + 1]) // 4
            it.iternext()
            it.iternext()
        return imgCopy

def diamondPredictDifferenceMap(img: np.ndarray) -> np.ndarray:
    """菱形预测的差值位图

    Args:
        img (np.ndarray): 灰度图像

    Returns:
        np.ndarray: 原图像与菱形预测结果的差值二维数组
    """
    imgDiamondPredicted = halfDiamondPredict(img, True)
    imgDiamondPredicted = halfDiamondPredict(imgDiamondPredicted, False)
    imgDiamondPredicted = imgDiamondPredicted.astype(np.int32)
    return imgDiamondPredicted - img

def embeddingByDifferenceMap(img: np.ndarray, bytes: list) -> Tuple[np.ndarray, int]:
    """根据差值直方图进行数据插入

    Args:
        img (np.ndarray): 原图像
        bytes (list): 要插入的序列

    Returns:
        np.ndarray: 插入数据后的图像
    """
    byteIndex = 0
    differenceMap = diamondPredictDifferenceMap(img)
    peakPoint, zeroPoint = getPeakAndZeroPoint(differenceMap)
    with np.nditer(differenceMap, flags=['multi_index'], op_flags=['readwrite']) as it:
        while not it.finished:
            indexX, indexY = it.multi_index
            if it[0] > peakPoint and it[0] < zeroPoint:
                img[indexX][indexY] += 1
            elif it[0] == peakPoint:
                byteIndex += 1
                if bytes[byteIndex] == 1:
                    img[indexX][indexY] += 1
            it.iternext()
    return img, byteIndex

if __name__ == "__main__":

    draw = False
    imgGray = readGrayImage()
    showGrayImageAndHist(imgGray, "嵌入数据前")
    byteList = generateRandom01(256000)
    imgEmbedded, bytesNum = embedding(imgGray, byteList)
    print("嵌入的字节数：", bytesNum)
    showGrayImageAndHist(imgEmbedded, "嵌入数据后")
    imgExtraciton, byteListExtraction = extract(imgEmbedded, bytesNum)
    showGrayImageAndHist(imgExtraciton, "提取数据后")
    
    print("提取出的数据完全正确！") if byteList[:bytesNum] == byteListExtraction else print("提取出的数据不正确！")
    print("图像无失真") if (imgGray == imgExtraciton).all() else print("图像存在失真")
    
    # 求菱形预测的差值位图
    imgEmbeddedByDifferenceMap, bytesNum2 = embeddingByDifferenceMap(imgGray, byteList)
    print("菱形预测差值直方图的嵌入容量：", bytesNum2)