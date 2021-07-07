import numpy as np
import matplotlib.pyplot as plt
import os
import sys


x = [0.520, 3.1, 8.0, 17.95, 28.65, 39.62, 50.65, 78, 104.6, 156.6, 208.6, 260.7, 312.50, 364.4, 416.3, 468, 494, 507, 520]
y = [5.288, 9.4, 13.84, 20.20, 24.90, 28.44, 31.10, 35, 36.9, 36.6, 34.6, 31.0, 26.34, 20.9, 14.8, 7.8, 3.7, 1.5, 0.2]
sx = [2, 30, 130, 350, 515]
sy = []
dy0 = 1.86548
dyn = -0.046115
n = 19
a = []
b = []
c = []
d = []
h = []


def solve(a, b, c, d):  # 使用追赶法求解M
    m = np.zeros(n)
    x = np.zeros(n)
    for i in range(1, n):
        m[i] = a[i] / b[i - 1]
        b[i] = b[i] - m[i] * c[i - 1]
        d[i] = d[i] - m[i] * d[i - 1]
    x[n - 1] = d[n - 1] / b[n - 1]
    for i in range(n - 2, -1, -1):
        x[i] = (d[i] - c[i] * x[i + 1]) / b[i]
    return x


def f(w, tx):
    return M[w]*(x[w+1]-tx)*(x[w+1]-tx)*(x[w+1]-tx)/6.0/h[w] + M[w+1]*(tx-x[w])*(tx-x[w])*(tx-x[w])/6.0/h[w] + (y[w]-M[w]*h[w]*h[w]/6.0)*((x[w+1]-tx)/h[w]) + (y[w+1]-M[w+1]*h[w]*h[w]/6.0)*((tx-x[w])/h[w])


def df(w, tx):
    return - M[w]*(x[w+1]-tx)*(x[w+1]-tx)/2.0/h[w] + M[w+1]*(tx-x[w])*(tx-x[w])/2.0/h[w] + (y[w+1]-y[w])/h[w] - (M[w+1]-M[w])*h[w]/6.0


def ddf(w, tx):
    return M[w]*(x[w+1]-tx)/h[w] + M[w+1]*(tx-x[w])/h[w]


def find_wh(tx):  # 寻找x在哪个分段
    w = 0
    for i in range(n - 1):
        if ((x[i] <= tx) and (tx <= x[i+1])):
            w = i
    return w


def work(tx):  # 计算在某一点的函数、一次导数、二次导数值
    print("x=%.0lf" % (tx))
    w = find_wh(tx)
    sy.append(f(w, tx))
    print("f=%.4lf" % (f(w, tx)))
    print("f'=%.4lf" % (df(w, tx)))
    print("f''=%.4lf\n" % (ddf(w, tx)))


os.chdir(sys.path[0])  # 转换工作路径/生成图在此目录

for i in range(n):  # 构造线性方程组
    if (i != n-1):
        h.append(x[i + 1] - x[i])
    b.append(2)
    if (i == 0):
        a.append(0)
        c.append(1)
        d.append(6.0 / h[0] * ((y[1] - y[0]) / h[0] - dy0))
    elif (i == n - 1):
        a.append(1)
        c.append(0)
        d.append(6.0 / h[i - 1] * (dyn - (y[i] - y[i - 1]) / h[i - 1]))
    else:
        a.append(1.0 * h[i - 1] / (h[i - 1] + h[i]))
        c.append(1.0 * h[i] / (h[i - 1] + h[i]))
        d.append(6.0 * (y[i - 1] / h[i - 1] / (h[i - 1] + h[i]) + y[i + 1] / h[i] / (h[i - 1] + h[i]) - y[i] / h[i - 1] / h[i]))

M = solve(a, b, c, d)
for tx in sx:
    work(tx)

xx = np.linspace(0.5, 520, 500)  # 将结果绘制成图
yy = []
for i in range(500):
    yy.append(f(find_wh(xx[i]), xx[i]))
plt.plot(sx, sy, 'bo')
plt.plot(x, y, 'bo', c='lightskyblue')
plt.plot(xx, yy)
plt.savefig('6-8.png')
plt.show()
