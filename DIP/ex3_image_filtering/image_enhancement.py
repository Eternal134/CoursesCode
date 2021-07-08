import abc
from ex3_image_filtering.spatial_smoothing import SpatialSmoothing
import numpy as np

class ImageEnhancement():
    """图像增强算法"""
    
    @abc.abstractmethod
    def enhanceImage(img: np.ndarray) -> np.ndarray:
        """图像增强算法

        Args:
            img (np.ndarray): 原始图像

        Returns:
            np.ndarray: 增强后图像
        """
        pass


class LaplacianEnhancement(ImageEnhancement):
    """拉普拉斯算子图像增强"""
    
    # 拉普拉斯算子
    laplacian = np.array([[0, -1, 0], [-1, 5, -1], [0, -1, 0]])
    
    def enhanceImage(self, img: np.ndarray) -> np.ndarray:
        
        imgEnhancement = np.copy(img)
        with np.nditer(img, flags=['multi_index']) as it:
            while not it.finished:
                imgEnhancement[it.multi_index] = SpatialSmoothing.matrixHadamardMean(img, self.laplacian, it.multi_index)
                it.iternext()
            
        return imgEnhancement
