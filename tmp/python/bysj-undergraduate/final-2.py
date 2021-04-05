#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import csv
import matplotlib.pyplot as plt
import seaborn as sns

filename = "/home/whu/Documents/data/cartographer/b2-2016-04-27-12-31-41.bag.pbstream.relation_metrics (copy).csv"



data = []

with open(filename) as f:
    reader = csv.reader(f)
    for row in reader:
        data.append(float(row[0]))


sns.distplot(data, bins=30)
plt.xlim(xmin=0)
plt.ylim(ymin=0)
plt.show()
