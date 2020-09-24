class Iris_Clustering():
    
    def __init__(self, my_c):
        
        self.c = my_c
        self.iris_file_name = "iris.txt"
        self.original_datas = []
        self.clustered_datas = []
        
    def read_iris_datas(self):
        
        with open(self.iris_file_name) as file_object:
            file_text = file_object.read().split('\n')
            
        for data in file_text:
            t_data = tuple([float(i) for i in data.split(',')[:3]])
            self.original_datas.append(t_data)
            
        # print(self.original_datas)


def main():
    
    my_c = 2
    iris_clustering = Iris_Clustering(my_c)
    iris_clustering.read_iris_datas()
    
if __name__ == "__main__":
    main()