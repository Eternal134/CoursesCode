import numpy as np
from math import sqrt, pi, exp

# ------------------------- 从文件中读取并分类样本 -------------------------

file_path = "iris.txt"

def getSampleFromFile():
    
    with open(file_path, 'r') as f:
        global samples
        samples = np.array([i.split(',')[:4] for i in f.read().split('\n')])

getSampleFromFile()
train_set = np.array([])
test_set = np.array([])

for i in range(len(samples)):
    
    if (i < 40) or (49 < i < 90) or (99 < i < 140):
        if train_set.size == 0:
            train_set = samples[i]
        else:
            # np.vstack()，垂直合并数组
            train_set = np.vstack((train_set, samples[i]))
    else:
        if test_set.size == 0:
            test_set = samples[i]
        else:
            test_set = np.vstack((test_set, samples[i]))

train_set = np.asfarray(train_set)
test_set = np.asfarray(test_set)
train_set_splited = np.array_split(train_set, 3)

# --------------------------- 计算均值向量 ------------------------------

ave_vectors = np.empty((3, 4))                                 # 均值向量

ave_vectors[0] = np.mean(train_set[: 40], axis = 0)
ave_vectors[1] = np.mean(train_set[40: 80], axis = 0)
ave_vectors[2] = np.mean(train_set[80:], axis = 0)

# ---------------------------- 计算协方差矩阵 ------------------------------

covariance = np.empty((3, 4, 4))                                # 协方差矩阵
covariance[0] = np.cov(train_set[: 40], rowvar = False)
covariance[1] = np.cov(train_set[40: 80], rowvar = False)
covariance[2] = np.cov(train_set[80:], rowvar = False)

# --------------------------- 最小误判概率判决------------------------------

correct_num = 0                                         # 判别正确的个数
for j in range(len(test_set)):
    # 对测试样本中的每个模式进行判别
    judges = np.empty((3, ))
    sample = test_set[j]
    for i in range(3):
        judges[i] = (sample - ave_vectors[i]).reshape(1, 4) @ np.linalg.inv(covariance[i]) @ \
            (sample - ave_vectors[i]).reshape(4, 1)
    wi = np.argmin(judges)                              # 三个判别中最小的那个就是分类结果
    if(wi == j // 10):
        correct_num += 1

print("最小误判概率判决的正确率为:\n{:.2f}%".format(correct_num * 100 / 30))

# --------------------------------- 最小损失判决 -------------------------------

# feafeature_probablity_density[i, j, k]表示：第i类中特征j的均值(k=0)和方差(k=1)
feature_probablity_density = np.zeros((3, 4, 2))
for i in range(3):
    # 对每个类
    for f in range(4):
        # 对每个特征求它们的均值和方差
        feature_probablity_density[i, f, 0] = np.mean(train_set_splited[i][:, f])
        feature_probablity_density[i, f, 1] = np.var(train_set_splited[i][:, f])

misjudgment_loss = np.array([[0, 1, 2], [1, 0, 3], [2, 3, 0]])          # 决策-损失表
class_conditional_probability = np.zeros((3, ))                         # 每个模式的类条件概率
judges = np.zeros((3, ))                                                # 模式对每个类的判决结果

correct_count = 0
for i in range(len(test_set)):
    # 对每个测试样本进行判决
    for j in range(3):
        # 对每个类带入类条件概率计算公式
        ccp = 1             # 测试样本的类条件概率
        judge = 0
        for f in range(4):
            # 对每个特征的高斯分布求概率
            mean = feature_probablity_density[j, f, 0]
            var = feature_probablity_density[j, f, 1]
            feature_value = test_set[i][f]
            ccp *= (1 / sqrt(2*pi) / sqrt(var)) * exp(- (feature_value - mean) ** 2 / 2 / var)
        class_conditional_probability[j] = ccp
        
    numerator = denominator = 0
    for j in range(3):
        # 对每个类进行判决
        for k in range(3):
            # 判决公式求和
            numerator += misjudgment_loss[j, k] * class_conditional_probability[k] * (1 / 3)
            denominator += class_conditional_probability[k] * (1 / 3)
        judges[j] = numerator / denominator
    
    wi = np.argmin(judges)
    if wi == i // 10:
        correct_count += 1
print("最小损失判决的正确率为:\n{:.2f}%".format(correct_count / len(test_set) * 100))