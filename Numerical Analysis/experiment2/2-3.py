import numpy as np
import scipy.special  # 通过这个包求第一类贝塞尔函数
import matplotlib.pyplot as plt
import os
import sys


def fzerotx(F, a, b):  # 书中伪代码翻译成 Python
    eps = 1e-10

    fa = F(a)
    fb = F(b)
    c = a
    fc = fa
    d = b - c
    e = d

    while fb != 0:
        if (fa * fb > 0):
            a = c
            fa = fc
            d = b - c
            e = d
        if abs(fa) < abs(fb):
            c = b
            b = a
            a = c
            fc = fb
            fb = fa
            fa = fc
        m = 0.5 * (a - b)
        tol = 2.0 * eps * max(abs(b), 1.0)
        if (abs(m) <= tol) or (fb == 0):
            break
        if (abs(e) < tol) or (abs(fc) <= abs(fb)):
            d = m
            e = m
        else:
            s = fb / fc
            if (a == c):
                p = 2.0 * m * s
                q = 1.0 - s
            else:
                q = fc / fa
                r = fb / fa
                p = s * (2.0 * m * q * (q - r) - (b - c) * (r - 1.0))
                q = (q - 1.0) * (r - 1.0) * (s - 1.0)
            if (p > 0):
                q = -q
            else:
                p = -p
            if (2.0 * p < 3.0 * m * q - abs(tol * q)) and (p < abs(0.5 * e * q)):
                e = d
                d = p / q
            else:
                d = m
                e = m
        c = b
        fc = fb
        if (abs(d) > tol):
            b = b + d
        else:
            b -= np.sign(b - a) * tol
        fb = F(b)
    return b


os.chdir(sys.path[0])  # 转换工作路径/生成图在此目录
x = np.arange(0, 31, 0.01)
y = scipy.special.j0(x)
zero = []
for i in range(len(x) - 1):
    if y[i] * y[i+1] < 0:
        zero.append(fzerotx(scipy.special.j0, x[i], x[i+1]))  # 找到有根区间，在这个区间运用 fzerotx 求零点
zero = np.array(zero)
for i in range(10):
    print('ZERO %d: x = %.10lf' % (i + 1, zero[i]))
plt.plot(x, np.zeros_like(x), '-')  # 绘制 x 轴
plt.plot(x, y, '-')                 # 绘制第一类贝塞尔函数
plt.scatter(zero, np.zeros_like(zero))  # 绘制零点
plt.tight_layout()
plt.savefig('2-3.png')
plt.show()
