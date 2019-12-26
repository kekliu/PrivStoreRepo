#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

x = [5, 10, 15, 20, 30, 40]
y1 = [294.855, 428.235, 563.401, 659.891, 859.951, 1031.771]
y2 = []

init_CPU_time = 3005.771

for i in y1:
    y2.append(init_CPU_time / i)

fig = plt.figure()

plt.xlabel('k value')

ax1 = fig.add_subplot(111)
ax1.plot(x, y1, 'cx-', linewidth=0.5, label='CPU time')
ax1.set_ylabel('CPU time (s)')
plt.xticks(x)
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
