import numpy as np

# ------------------------- get and sort samples -------------------------

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
            train_set = np.vstack((train_set, samples[i]))
    else:
        if test_set.size == 0:
            test_set = samples[i]
        else:
            test_set = np.vstack((test_set, samples[i]))

train_set = np.asfarray(train_set)
test_set = np.asfarray(test_set)

# --------------------- calculate average vector -------------------------

ave_vectors = np.empty((3, 4))                                 # 均值向量

ave_vectors[0] = np.mean(train_set[: 40], axis = 0)
ave_vectors[1] = np.mean(train_set[40: 80], axis = 0)
ave_vectors[2] = np.mean(train_set[80:], axis = 0)

# --------------------- calculate covariance matrix ----------------------

covariance = np.empty((3, 4, 4))                                # 协方差矩阵
covariance[0] = np.cov(train_set[: 40], rowvar = False)
covariance[1] = np.cov(train_set[40: 80], rowvar = False)
covariance[2] = np.cov(train_set[80:], rowvar = False)

# ------------------ minimun probability of misjudgment ------------------

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