from ex3_image_filtering.image_enhancement import LaplacianEnhancement, ImageEnhancement
from . import SpatialSmoothing

class ImageFliterFactory():
    """图像滤波算法工厂
    """
    
    @classmethod
    def lowPassFliterFactory(cls) -> SpatialSmoothing:
        """临域平滑算法工厂
        """
        return SpatialSmoothing.LowPassFilter()
    
    @classmethod
    def medianFliterFactory(cls) -> SpatialSmoothing:
        """中值滤波算法工厂"""
        return SpatialSmoothing.MedianFilter()
    
    @classmethod
    def laplacianEnhancementFactory(cls) -> ImageEnhancement: 
        """拉普拉斯算子图像增强工厂"""
        return LaplacianEnhancement()