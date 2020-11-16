import csv
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from IPython.display import display

book_types = ['推理', '文学', '诗歌', '计算机', '科普', '爱情', '心理', '经济学', '历史', '漫画']
# data_np，统计数据的数组，每一行表示一种书的类型，第一列记录该类型的样本数，其后列记录每本书的页均价
data_np = np.zeros((len(book_types), 1000))
# 统计样本中出版社的出现频率
company_stat = {}
# 统计图书的价格与评分
dtype = np.dtype([('价格', float), ('评分', float)])
price_and_rank_np = np.ndarray((0, 2), dtype = dtype)

file_path = "book_item.csv"
with open(file_path) as f:
    reader = csv.reader(f)
    for item in reader:
        index = book_types.index(item[0])
        data_np[index, 0] += 1
        data_np[index, int(data_np[index, 0])] =  float(item[-2]) / int(item[-1])
        # 统计出版社出现的频率
        company = item[4]
        company_stat[company] = company_stat.get(company, 0) + 1
        # 统计价格与评分
        price_and_rank_np = np.append(price_and_rank_np, np.array((float(item[-2]) / int(item[-1]), item[2]), \
            dtype = dtype))
price_and_rank_np = np.sort(price_and_rank_np, order = '评分')          # 根据评分进行排序
print("评分与价格相关性矩阵：\n", \
    np.corrcoef(price_and_rank_np['评分'], price_and_rank_np['价格']))

# 表示价格与书类型关系
price_and_type_pd = pd.DataFrame(np.array([np.mean(data_np[:, 1:], axis = 1), np.std(data_np[:, 1:], axis = 1), \
    data_np[:, 0]]).T, index = book_types, columns = ['页均价', '标准差', '样本数'])
# 找出出版社出现频率前10的出版社
company_stat = list(company_stat.items())
company_stat.sort(key = lambda x: x[1], reverse = True)
top10_companys = [x[0] for x in company_stat[:10]]
# 对出现频率前10的出版社再统计价格
companys_data_np = np.zeros((len(top10_companys), 1000))
with open(file_path) as f:
    reader = csv.reader(f)
    for item in reader:
        if item[4] in top10_companys:
            index = top10_companys.index(item[4])
            companys_data_np[index, 0] += 1
            companys_data_np[index, int(companys_data_np[index, 0])] = float(item[-2]) / int(item[-1])
            
price_and_company_pd = pd.DataFrame(np.array([np.mean(companys_data_np[:, 1:], axis = 1), \
    np.std(companys_data_np[:, 1:], axis = 1), companys_data_np[:, 0]]).T, index = top10_companys, \
        columns = ['页均价', '标准差', '样本数'])

pd.set_option('display.unicode.ambiguous_as_wide', True)
pd.set_option('display.unicode.east_asian_width', True)
pd.set_option('display.precision', 2)
print(price_and_type_pd)
print(price_and_company_pd)

fontsize = 4
dpi = 900
# 绘制页均价与图书类型统计关系直方图
plt.figure(1, figsize = (3, 2))
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
price_and_type_pd.iloc[:, [0, 1]].plot.bar()                     # 设绘制直方图
plt.xticks(fontsize = fontsize)
plt.yticks(fontsize = fontsize)
plt.tight_layout()
plt.ylabel("页均价/元", fontsize = fontsize)
plt.title("页均价与图书类型直方图", fontsize = fontsize)
plt.grid(axis = 'y')
plt.savefig("页均价与图书类型.png", dpi = dpi)
plt.close()
# plt.show()
# 绘制页均价与出版社统计关系直方图
plt.figure(2, figsize = (3, 2))
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
price_and_company_pd.iloc[:, [0, 1]].plot.bar()
plt.xticks(fontsize = fontsize)
plt.yticks(fontsize = fontsize)
plt.tight_layout()
plt.ylabel("页均价/元", fontsize = fontsize)
plt.title("页均价与出版社直方图", fontsize = fontsize)
plt.grid(axis = 'y')
plt.savefig("页均价与出版社.png", dpi = dpi)
plt.close()
# plt.show()
# 绘制页均价与评分统计关系曲线图
plt.figure(3, figsize = (3, 2))
plt.plot(price_and_rank_np['评分'], price_and_rank_np['价格'], color = 'pink', linewidth = 1)
plt.grid(axis = 'y')
plt.tight_layout()
plt.title("页均价与评分曲线图", fontsize = fontsize)
plt.ylabel("页均价/元", fontsize = fontsize)
plt.xlabel("评价", fontsize = fontsize)
plt.savefig("页均价与评分曲线图.png", dpi = dpi)
plt.close()