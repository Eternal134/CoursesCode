import numpy as np
import math
import abc

class SpatialSmoothing:
    """空间域平滑算法
    """
    @abc.abstractmethod
    def smoothing(cls, img: np.ndarray, mask: np.ndarray, threshold = 0) -> np.ndarray:
        """平滑算法

        Args:
            img (np.ndarray): 原图像
            mask (np.ndarray): 平滑掩膜

        Returns:
            np.ndarray: 平滑处理之后的图像
        """
        pass
    
    @classmethod
    def matrixHadamardMean(cls, array: np.ndarray, mask: np.ndarray, index: tuple) -> float:
        """数组某索引周围元素与掩膜矩阵运算乘积之和"""
        
        productList = []
        maskRowCount, maskColCount = mask.shape
        arrayRowCount, arrayColCount = array.shape
        indexX, indexY = index
        for rowIndex in range(-(maskRowCount//2), math.ceil(maskRowCount/2)):
            for colIndex in range(-(maskColCount//2), math.ceil(maskColCount/2)):
                row, col = indexX + rowIndex, indexY + colIndex
                if row >= 0 and row < arrayRowCount and col < arrayColCount and col >= 0:
                    product = array[row][col] * \
                        mask[rowIndex + (maskRowCount // 2)][colIndex + (maskColCount // 2)]
                    productList.append(product)
        if len(productList) == 0:
            return array[index]
        else:
            return sum(productList)
        
        
    def findMedianInMask(array: np.ndarray, mask: np.ndarray, index: tuple) -> float:
        """在模板区域找到中间值

        Args:
            array (np.ndarray): 数组
            mask (np.ndarray): 模板
            index (tuple): 当前要找的位置

        Returns:
            float: 中间值
        """
        selectedList = []
        maskRowCount, maskColCount = mask.shape
        arrayRowCount, arrayColCount = array.shape
        indexX, indexY = index
        with np.nditer(mask, flags=['multi_index']) as it:
            while not it.finished:
                itRow, itCol = it.multi_index
                if it[0] > 0:
                    rowIndex, colIndex = itRow - maskRowCount//2, itCol - maskColCount//2
                    arrayRow, arrayCol = indexX + rowIndex, indexY + colIndex
                    if arrayCol >= 0 and arrayCol < arrayColCount and \
                        arrayRow >= 0 and arrayRow < arrayRowCount:
                            selectedList.append(array[arrayRow][arrayCol])
                it.iternext()
        return sorted(selectedList)[len(selectedList) // 2]


class LowPassFilter(SpatialSmoothing):
    """低通滤波算法
    """
    @classmethod
    def smoothing(cls, img: np.ndarray, mask: np.ndarray, threshold = 0) -> np.ndarray:
        """平滑算法，当参数threshold>0时，此方法就变成了超限像素平滑法

        Args:
            img (np.ndarray): 原图像
            mask (np.ndarray): 平滑掩膜

        Returns:
            np.ndarray: 平滑处理之后的图像
        """
        imgSmoothed = np.copy(img)
        with np.nditer(img, op_flags=['readwrite'], flags=['multi_index']) as it:
            while not it.finished:
                if it[0] == 0:
                    print()
                # 临域加权计算出的像素值
                weightedPixel = cls.matrixHadamardMean(img, mask, it.multi_index)
                # 原像素值
                originalPixel = imgSmoothed[it.multi_index[0]][it.multi_index[1]]
                if abs(weightedPixel - originalPixel) > threshold:
                    # 当他们的差值大于阈值时，才更新
                    imgSmoothed[it.multi_index[0]][it.multi_index[1]] = weightedPixel
                it.iternext()
        return imgSmoothed
    
    
class MedianFilter(SpatialSmoothing):
    """中值滤波
    """
    
    @classmethod
    def smoothing(cls, img: np.ndarray, mask: np.ndarray, threshold: int = 0) -> np.ndarray:
        """平滑算法

        Args:
            img (np.ndarray): 原图像
            mask (np.ndarray): 掩膜
            threshold (int): 阈值

        Returns:
            np.ndarray: 平滑处理之后的图像
        """
        imgSmoothed = np.copy(img)
        with np.nditer(img, flags=['multi_index']) as it:
            while not it.finished:
                imgSmoothed[it.multi_index] = cls.findMedianInMask(img, mask, it.multi_index)
                it.iternext()
        return imgSmoothed