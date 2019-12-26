#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

x = [5, 10, 15, 20, 30, 40]
y1 = [0.129404017,
      0.127603436,
      0.12180731,
      0.119345313,
      0.115299593,
      0.114449213
      ]
y2 = [0.057125783,
      0.110133084,
      0.149040636,
      0.184071968,
      0.240083339,
      0.298468893
      ]

fig = plt.figure()

plt.xlabel('k value')

ax1 = fig.add_subplot(111)
ax1.plot(x, y1, 'cx-', linewidth=0.5, label='P')
ax1.set_ylabel('Ratio')
plt.xticks(x)
# ax1.set_title("Double Y axis")

ax1.plot(x, y2, 'r+--', linewidth=0.5, label='R')

plt.legend(loc='upper left')

plt.show()
