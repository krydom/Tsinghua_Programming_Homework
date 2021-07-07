import numpy as np
import matplotlib.pyplot as plt
import os
import sys


os.chdir(sys.path[0])  # 转移工作路径/生成图片在本文件夹下
h = np.array([10**x for x in np.arange(-16, 0.1, 0.1)])  # 例1.4中各变量的规定
M = 1
x = 1
e = 10**-16

plt.rcParams['xtick.direction'] = 'in'  # 刻度在内
plt.rcParams['ytick.direction'] = 'in'
plt.gca().set_xlim([10**-16, 10**0])    # 规定坐标范围
plt.gca().set_ylim([10**-17, 10**1])

plt.xlabel('步长h', fontproperties='SimHei', fontsize=11)
plt.ylabel('误差', fontproperties='SimHei', fontsize=11)

plt.plot(h, abs((np.sin(x + h) - np.sin(x)) / h - np.cos(x)), '-', label='实际总误差')  # 制图
plt.plot(h, M * h / 2, '--', label='截断误差')
plt.plot(h, 2 * e / h, '--', label='舍入误差')
plt.plot(h, M * h / 2 + 2 * e / h, '--', label='总误差限')
plt.loglog()                                                   # 对数横纵坐标
plt.legend(prop={'family': 'SimHei', 'size': 11})              # 显示图例

plt.xticks(np.array([10**x for x in np.arange(-16, 2, 2.0)]))  # 规定刻度间隔
plt.yticks(np.array([10**x for x in np.arange(-17, 3, 2.0)]))

plt.savefig("1-1.png")
plt.show()
