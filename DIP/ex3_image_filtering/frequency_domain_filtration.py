import abc
import numpy as np

class FrequencyFiltration():
    """频率域滤波"""
    
    @abc.abstractmethod
    def filter(self, img: np.ndarray) -> np.ndarray:
        """滤波

        Args:
            img (np.ndarray): 原图像

        Returns:
            np.ndarray: 滤波后图像
        """
        pass
    
    
class IdealLowPassFiltration(FrequencyFiltration):
    """理想低通滤波器"""
    
    def filter(self, img: np.ndarray) -> np.ndarray:
        """滤波

        Args:
            img (np.ndarray): 原图像

        Returns:
            np.ndarray: 滤波后图像
        """
        pass