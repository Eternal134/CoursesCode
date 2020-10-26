import numpy as np

class Iris_Cluster():
    
    def __init__(self):
        
        self.c = 3
        self.iris_file_name = "iris.txt"
        self.original_datas = [[], [], []]
        self.clustered_datas = []
        self.centers = []
        self.clusters_std = []
        self.J_value = 0
        
    def read_iris_datas(self):
        
        with open(self.iris_file_name) as file_object:
            file_text = file_object.read().split('\n')
            
        for data, i in zip(file_text, range(151)):
            t_data = tuple([float(i) for i in data.split(',')[:4]])
            self.original_datas[i // 50].append(t_data)
            
    def calculate_J_value(self):
        # 计算J值
        self.clusters_distances.clear()
        for cluster, center in zip(self.clustered_datas, self.centers):
            d = 0
            for data in cluster:
                d += pow(iris_Euclidean_distance(data, center), 2)
            self.clusters_distances.append(d)
        self.J_value = sum(self.clusters_distances)
        

def iris_Euclidean_distance(iris1, iris2):
    # 计算欧式距离
    d = 0
    for i in range(len(iris1)):
        d = d + pow(iris1[i] - iris2[i], 2)
    return pow(d, 0.5)


iris_cluster = Iris_Cluster()
iris_cluster.read_iris_datas()
iris_cluster.calculate_J_value()
print(iris_cluster.J_value)