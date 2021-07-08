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
        
        imgFft = np.fft.fftshift(np.fft.fft2(img))
        rows,cols=img.shape 
        # 计算频谱中心
        crow,ccol=int(rows/2),int(cols/2) 
        # 生成rows行cols的矩阵，数据格式为uint8 
        mask=np.zeros((rows,cols),np.uint8) 
        # 将靠近频谱中心的部分低通信息 设置为1，属于低通滤波
        index = 30
        mask[crow-index: crow+index,ccol-index: ccol+index]=1 
        # 计算低通滤波
        f1Shift=imgFft*mask
        
        fIshift=np.fft.ifftshift(f1Shift) 
        imgRes=np.fft.ifft2(fIshift) 
        imgRes=np.abs(imgRes)
        imgRes=(imgRes-np.amin(imgRes))/(np.amax(imgRes)-np.amin(imgRes))
        return imgRes