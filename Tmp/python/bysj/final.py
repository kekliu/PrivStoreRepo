#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 本文件用于解析Cartographer日志，获取时间信息

import re
import csv
import matplotlib.pyplot as plt
import seaborn as sns

data = []

if __name__ == '__main__':
    filename = '/home/whu/Documents/PycharmProjects/test/bysj/asserts/error-distribution'




    file = open(filename)
    while 1:
        lines = file.readlines(1000)
        if not lines:
            break
        for line in lines:
            line = line.replace('\n', '')
            data.append(float(line))

# plt.hist(data, bins=50, color='steelblue')
# plt.show()

sns.distplot(data, bins=30)
plt.xlim(xmin=0)
plt.ylim(ymin=0)
plt.show()




