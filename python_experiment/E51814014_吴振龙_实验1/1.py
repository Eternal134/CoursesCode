f = [0, 1]              # Fibonacci数列
for i in range(2, 100):
    f.append(f[i - 1] + f[i - 2])
ratio = [f[i] / f[i + 1] for i in range(len(f) - 1)]              # 数列的前项比后项

print(ratio[:10], '\n...\n', ratio[-10:])