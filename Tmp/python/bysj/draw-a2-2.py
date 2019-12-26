#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

x = [1, 2, 3, 4, 5, 6]
y1 = [
    0.10007155,
    0.115191506,
    0.142112612,
    0.16748643,
    0.195928813,
    0.206762265
]

y2 = [0.982621616,
      0.774807804,
      0.646068867,
      0.509819756,
      0.400607274,
      0.27526003
      ]

fig = plt.figure()

plt.xlabel('min ratio')

ax1 = fig.add_subplot(111)
ax1.plot(x, y1, 'cx-', linewidth=0.5, label='P')
ax1.set_ylabel('Ratio')
plt.xticks(x, ('0.3', '0.15', '0.075', '0.0375', '0.01875', '0.009375'))
# ax1.set_title("Double Y axis")

ax1.plot(x, y2, 'r+--', linewidth=0.5, label='R')

plt.legend(loc='upper right')

plt.show()
