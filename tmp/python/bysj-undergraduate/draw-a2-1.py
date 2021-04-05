#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

x = [1, 2, 3, 4, 5, 6]
y1 = [3021.311,
      2256.701,
      1668.741,
      1201.061,
      865.491,
      634.801
      ]
y2 = []

init_CPU_time = 3021.311

for i in y1:
    y2.append(init_CPU_time / i)

fig = plt.figure()

plt.xlabel('min ratio')

ax1 = fig.add_subplot(111)
ax1.plot(x, y1, 'cx-', linewidth=0.5, label='CPU time')
ax1.set_ylabel('CPU time (s)')
plt.xticks(x, ('0.3', '0.15', '0.075', '0.0375', '0.01875', '0.009375'))
# ax1.set_title("Double Y axis")

ax2 = ax1.twinx()  # this is the important function
ax2.plot(x, y2, 'r+--', linewidth=0.5, label='Time Ratio')
ax2.set_ylabel('Time Ratio')

# handles, labels = [], []
# for ax in fig.axes:
#     for h, l in zip(*ax.get_legend_handles_labels()):
#         handles.append(h)
#         labels.append(l)
#
# plt.legend(handles, labels, loc='center right')

h1, l1 = ax1.get_legend_handles_labels()
h2, l2 = ax2.get_legend_handles_labels()

plt.legend(h1 + h2, l1 + l2, loc='center right')

plt.show()
