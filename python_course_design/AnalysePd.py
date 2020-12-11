import pandas as pd
import numpy as np
from pandas.plotting import table
from IPython.display import display
from matplotlib import pyplot as plt
from collections import Counter
''' 设置pandas的输出样式 '''
pd.set_option('display.unicode.ambiguous_as_wide', True)
pd.set_option('display.unicode.east_asian_width', True)
pd.set_option('display.precision', 2)
# 设置文件路径
file_path = "book_item.csv"
# 从本地读取文件到DataFrame格式
all_items_pd = pd.read_csv(file_path, encoding = "utf-8")
# 计算每个item的页均价
unit_price_pd = pd.Series(all_items_pd['价格'] / all_items_pd['页数'], name='页均价')
# 连接到总数据中
all_items_pd = pd.concat([all_items_pd, unit_price_pd], axis = 1)


def getYear(x):
    if '-' in x:
        return x.split('-')[0]
    elif '年' in x:
        return x.split('年')[0]
    return ""
all_items_pd['出版日期'] = all_items_pd['出版日期'].apply(getYear)

xlsl = pd.ExcelWriter('统计数据.xls')

def getStat(direction):
    """ 根据direction获取想要的统计数据，比如direction是图书类型，则此函数可以统计与图书类型有关的统计数据 """
    # 设置感兴趣的统计类型
    stat_types = ['页均价', '中位数', '标准差', '样本数']
    """ 先获取统计方向direction上的出现频率最高的10个分量，如果direction是出版日期，则统计前20个分量 """
    if direction != '出版日期':
        top_direction = [i[0] for i in Counter(all_items_pd[direction]).most_common(10)]
    else:
        top_direction = [i[0] for i in Counter(all_items_pd[direction]).most_common(20) if i[0]]
        # 按年份递增排序
        top_direction.sort(key = lambda x: int(x))
    # 表示统计数据的DataFrame对象，每行是一个direction的一个分量，各列的含义见stat_types
    stat_pd = pd.DataFrame(np.zeros((len(top_direction), len(stat_types))), index = top_direction, columns = stat_types)
    
    for index in stat_pd.index:
        ''' 遍历stat_pd的每个行索引，对每个index: 
        all_items_pd.loc[all_items_pd[direction] == index]可以索引到all_items_pd中所有direction等于index的行，
        再索引'页均价'列，最后对索引到的结果调用求均值和求标准差方法 '''
        stat_pd.loc[index][stat_types[0]] = all_items_pd.loc[all_items_pd[direction] == index]['页均价'].mean()
        stat_pd.loc[index][stat_types[1]] = all_items_pd.loc[all_items_pd[direction] == index]['页均价'].median()
        stat_pd.loc[index][stat_types[2]] = all_items_pd.loc[all_items_pd[direction] == index]['页均价'].std()
        stat_pd.loc[index][stat_types[3]] = all_items_pd.loc[all_items_pd[direction] == index]['页均价'].size
    print(stat_pd)
    """ 绘图 """
    # 设置正常显示中文
    plt.rcParams['font.sans-serif'] = ['SimHei']
    plt.rcParams['axes.unicode_minus'] = False
    # 设置保存图片的分辨率
    dpi = 400

    title = direction + "与页均价统计关系"
    # 绘制前3列，最后一列的样本数不绘制图形
    stat_pd.iloc[:, :3].plot()
    plt.title(title)
    plt.xticks(range(len(top_direction)), top_direction, rotation = -60)
    plt.grid(ls = '-.')
    plt.tight_layout()
    plt.savefig(title + '.png', dpi = dpi)
    # 保存excel文件
    stat_pd.to_excel(xlsl)

directions = ['图书类型', '作者', '出版公司', '出版日期']
for d in directions:
    getStat(d)