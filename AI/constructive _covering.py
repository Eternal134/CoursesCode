import numpy as np
import pandas as pd
from math import sqrt
from sklearn.model_selection import train_test_split
from IPython import display
# ******************************* 从文本中读取数据 *******************************
file_path = "iris.txt"
# 前四列表示特征向量，第五列表示升维的第n+1维，第六列表示所属类别，第七列表示是否已学习
data_np = np.zeros((150, 7))
with open(file_path) as f:
    data_li = f.read().split('\n')
for i in range(len(data_li)):
    data = data_li[i].split(',')
    if data[-1] == "Iris-setosa":
        data[-1] = 1
    elif data[-1] == "Iris-versicolor":
        data[-1] = 2
    else:
        data[-1] = 3
    data.append(0)
    data.append(0)
    data_np[i] = data
data_np[:, [4, 5]] = data_np[:, [5, 4]]
    
# ************************************ 归一化 *****************************************
max_values = np.max(data_np, axis = 0)[:4]
min_values = np.min(data_np, axis = 0)[:4]
for data in data_np:
    data[:4] = (data[:4] - min_values) / (max_values - min_values)

# ************************************* 升维 *******************************************
d = lambda x: sqrt(sum([i * i for i in x]))
R = max([d(x[:4]) for x in data_np])
for data in data_np:
    data[4] = sqrt(R ** 2 - d(data[:4]) ** 2)
# ************************************ 十字交叉法 ***************************************
covers_nums = []                        # 覆盖数
total_rate = []                         # 总识别率
recognizable_nums = []                  # 可识别数
recognizable_correct_nums = []          # 可识别正确数
unrecognizable_nums = []                # 不可识别数
unrecognizable_correct_nums = []        # 不可识别样本正确数
recognizable_correct_rate = []          # 可识别的正确率
unrecognizable_correct_rate = []        # 不可识别的正确率
for m in range(10):
# ************************************ 计算覆盖集 ***************************************
    train_set_total, test_set = train_test_split(data_np, test_size = 0.1)
    train_set = train_set_total.copy()
    covering_set = np.array([])
    while len(train_set):
        # 直到所有样本被标记为已学习为止
        wi = train_set[np.random.randint(0, len(train_set))]
        try:
            max_dot = max([np.dot(wi[:5], data[:5]) for data in train_set if data[5] != wi[5]])
        except ValueError:
            # 出现此错误说明训练集中只剩下一类，应计算类内内积的最大值作为覆盖集的边界
            max_dot = min([np.dot(wi[:5], data[:5]) for data in train_set])
            covering_set = np.append(covering_set, np.array([np.append(wi[:6], max_dot)]), axis = 0)
            break
        i = 0
        while i < train_set.shape[0]:
            # 将在此覆盖集内的样本从训练集中移除
            if np.dot(wi[:5], train_set[i][:5]) > max_dot:
                train_set = np.delete(train_set, i, axis = 0)
            else:
                i += 1
        if len(covering_set) == 0:
            covering_set = np.array([np.append(wi[:6], max_dot)])
        else:
            covering_set = np.append(covering_set, np.array([np.append(wi[:6], max_dot)]), axis = 0)
    covers_nums.append(len(covering_set))
# ******************************* 测试 *******************************
    recognizable_num = 0
    recognizable_correct_num = 0
    unrecognizable_correct_num = 0
    unrecognizable_num = 0
    correct_num = 0
    for data in test_set:
        # 距离中心最近决策方案
        covers_result = [np.dot(cover[:5], data[:5]) for cover in covering_set]         # 计算到每个覆盖中心的内积
        max_index = covers_result.index(max(covers_result))                             # 找到内积最大的那个作为分类目标
        if covering_set[max_index][5] == data[5]:                                    
            # 如果分类结果与理论结果相同，correct_num加 1
            correct_num += 1
        for i in range(len(covers_result)):
            # 统计可识别样本数及可识别样本中正确的个数
            if covers_result[i] >= covering_set[i][-1]:
                recognizable_num += 1
                if covering_set[max_index][5] == data[5]:
                    recognizable_correct_num += 1
                break
    recognizable_nums.append(recognizable_num)
    recognizable_correct_nums.append(recognizable_correct_num)
    unrecognizable_num = len(test_set) - recognizable_num
    unrecognizable_nums.append(unrecognizable_num)
    unrecognizable_correct_num = correct_num - recognizable_correct_num
    unrecognizable_correct_nums.append(unrecognizable_correct_num)
    total_rate.append(correct_num / len(test_set))
    recognizable_correct_rate.append(recognizable_correct_num / recognizable_num)
    try:
        unrecognizable_correct_rate.append(unrecognizable_correct_num / unrecognizable_num)
    except ZeroDivisionError:
        pass
    
if len(unrecognizable_correct_rate) == 0:
    unrecognizable_correct_rate = [1]
    
rates_pd = pd.DataFrame({
        "覆盖数": sum(covers_nums) / len(covers_nums), \
        "可识别样本数": sum(recognizable_nums) / len(recognizable_nums), \
        "可识别样本正确数": sum(recognizable_correct_nums) / len(recognizable_correct_nums), \
        "可识别样本的正确率": sum(recognizable_correct_rate) / len(recognizable_correct_rate), \
        "不可识别样本数": sum(unrecognizable_nums) / len(unrecognizable_nums), \
        "不可识别样本正确数": sum(unrecognizable_correct_nums) / len(unrecognizable_correct_nums), \
        "不可识别样本的正确率": sum(unrecognizable_correct_rate) / len(unrecognizable_correct_rate), \
        "总正确率": sum(total_rate) / len(total_rate)}, index = ['iris'])

pd.set_option('display.unicode.ambiguous_as_wide', True)
pd.set_option('display.unicode.east_asian_width', True)
pd.set_option('colheader_justify', 'center')
pd.set_option('display.precision', 2)
for col in rates_pd.columns:
    if '率' in col:
        rates_pd[col] = rates_pd[col].apply(lambda x: format(x, '.2%'))
print(rates_pd)