import numpy as np

train_set1 = []
train_set2 = []
train_set3 = []
train_set = []
test_set = []
recognition_num = []

def read_data():
    path = "iris.txt"
    with open(path, 'r') as f:
        text = f.read()
    text_list = text.split('\n')
    for i in range(len(text_list)):
        text_list[i] = [float(j) for j in text_list[i].split(',')[:4]]
        text_list[i].append(i // 50)
        if i < 40:
            train_set1.append(text_list[i][:4])
        elif 50 <= i < 90:
            train_set2.append(text_list[i][:4])
        elif 100 <= i < 140:
            train_set3.append(text_list[i][:4])
        else:
            test_set.append(text_list[i])
            
def fisher_calculate(i1, i2):
    
    t1 = np.matrix(train_set[i1])
    t2 = np.matrix(train_set[i2])
    m1 = np.mean(t1[:, :4], axis = 0)
    m2 = np.mean(t2[:, :4], axis = 0)
    sw1 = np.zeros((4, 4))
    sw2 = np.zeros((4, 4))
    for j in range(40):
        sw1 += (t1[j] - m1).T * (t1[j] - m1)
        sw2 += (t2[j] - m2).T * (t2[j] - m2)
    sw = sw1 + sw2
    inverse_sw = np.linalg.inv(sw)
    u = inverse_sw @ (m1 - m2).T
    m1_wave = u.T @ m1.T
    m2_wave = u.T @ m2.T
    yt = ((m1_wave + m2_wave) / 2)[0]
    correct_num = [0, 0]
    recognition_numi = [0, 0]
    for pattern in test_set:
        y = np.dot(u.T, pattern[:4])[0]
        w = i1 if y >= yt else i2
        index = 0 if w == i1 else 1
        if pattern[4] == i1 or pattern[4] == i2:
            recognition_numi[index] += 1
            if w == pattern[4] or (w == 1 and pattern[4] == i2):
                correct_num[index] += 1
    global recognition_num
    return [correct_num, recognition_numi]
    
read_data()
correct_num = []
train_set = [train_set1, train_set2, train_set3]
value = fisher_calculate(0, 1)
value += fisher_calculate(0, 2)
value += fisher_calculate(1, 2)
correct_num = [i for x in value[::2] for i in x]
recognition_num = [i for x in value[1::2] for i in x]
correct_rate = [correct_num[i] / recognition_num[i] for i in range(len(correct_num))]
print("wi / wj:")
[print('%.2f' % x, end = ' ') for x in correct_rate]
print('\n%.2f' % (sum(correct_rate) / len(correct_rate)))