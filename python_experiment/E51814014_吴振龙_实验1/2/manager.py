import csv
import os

class Manager():

    def __init__(self):

        self.file_path = os.path.dirname(__file__) + "\\infos.csv"          # 在当前目录下拼接得到文件路径
        self.infos_list = []
        self.read_file()

    def read_file(self):
        ''' 从文件中读取数据 '''
        f = open(self.file_path, 'r')
        for read in csv.reader(f):
            if read:
                self.infos_list.append(read)

    def save_file(self):
        ''' 将数据保存到文件 '''
        with open(self.file_path, 'w', newline = '') as f:
            writer = csv.writer(f)
            for info in self.infos_list:
                writer.writerow(info)

    def add_item(self, item):
        ''' 增加一条记录
            item: 包含记录信息的列表 '''
        self.infos_list.append(item)
        self.save_file()

    def del_item(self, num):
        ''' 删除一条记录，num为记录的编号 '''
        for info in self.infos_list:
            self.infos_list.remove(info)
            self.save_file()
            return True