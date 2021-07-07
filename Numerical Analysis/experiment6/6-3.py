import numpy as np
import matplotlib.pyplot as plt
import os
import sys


t = [1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8]
y = [33.40, 79.50, 122.65, 159.05, 189.15, 214.15, 238.65, 252.2, 267.55, 280.50, 296.65, 301.65, 310.40, 318.15, 325.15]
m = 15


def construct(type):  # 按照书中6.28生成A矩阵
    if (type == 1):
        A = np.zeros((m, 3))
        for i in range(m):
            A[i] = [1, t[i], t[i] * t[i]]
    else:
        A = np.zeros((m, 2))
        for i in range(m):
            A[i] = [1, t[i]]
    return A


def work(type):  # 实现书中算法6.2
    A = construct(type)
    G = np.matmul(A.T, A)
    if (type == 1):
        b = np.matmul(A.T, np.transpose(y))
    else:
        b = np.matmul(A.T, np.transpose(list(map(np.log, y))))
    L = np.linalg.cholesky(G)
    x = np.linalg.solve(L, b)
    x = np.linalg.solve(L.T, x)
    if (type == 2):
        x[0] = np.exp(x[0])
    return x


os.chdir(sys.path[0])  # 转换工作路径/生成图在此目录

x1 = work(1)  # 进行曲线拟合
x2 = work(2)

s1 = 0  # 计算误差，输出结果
s2 = 0
for i in range(m):
    tmp = x1[0]+x1[1]*t[i]+x1[2]*t[i]*t[i] - y[i]
    s1 += tmp * tmp
    tmp = x2[0]*np.exp(x2[1]*t[i]) - y[i]
    s2 += tmp * tmp
s1 = np.sqrt(s1 / m)
s2 = np.sqrt(s2 / m)
print("y1=%.4lf+%.4lft%.4lft^2" % (x1[0], x1[1], x1[2]))
print("mean-square error=%.4lf\n" % s1)
print("y2=%.4lfe^(%.4lft)" % (x2[0], x2[1]))
print("mean-square error=%.4lf\n" % s2)

x = np.linspace(0.5, 8.5, 50)  # 将结果绘制成图
y1 = []
y2 = []
for i in range(50):
    y1.append(x1[0] + x1[1] * x[i] + x1[2] * x[i] * x[i])
    y2.append(x2[0] * np.exp(x2[1] * x[i]))
plt.plot(t, y, 'bo')
plt.plot(x, y1, label='a+bt+ct^2')
plt.plot(x, y2, label='ae^(bt)')
plt.legend()
plt.savefig('6-3.png')
plt.show()
