#!/usr/bin/env python3

import csv
import datetime
import matplotlib.pyplot as plt
import numpy as np


class Point(object):
    def __init__(self, name, attr, timestamp, x, y, z, error):
        self.name = name
        self.attr = attr
        self.timestamp = timestamp
        self.x = x
        self.y = y
        self.z = z
        self.error = error

    def __str__(self):
        return [self.name, self.timestamp, self.x, self.y].__str__()


def load_point_list(filename):
    point_list_ = []
    xs_ = []
    ys_ = []
    with open(filename) as f:
        reader = csv.reader(f)
        data = list(reader)
        for e in data:
            if e[3] == '-': continue
            point_list_.append(
                Point(e[0],
                      e[1],
                      datetime.datetime.strptime(e[2], '%m/%d/%Y %H:%M:%S'),
                      float(e[3]),
                      float(e[4]),
                      float(e[6]),
                      float(e[8])))
            xs_.append(float(e[3]))
            ys_.append(float(e[4]))
            print('{%s,%s},' % (e[3], e[4]))
        return point_list_, xs_, ys_


def add_text_for_points(*args):
    for pts in args:
        for e in pts:
            plt.text(e.x, e.y, e.name, fontsize=7)


pts1, xs, ys = load_point_list('/home/whu/Documents/data/17F/1.csv')
# pts2, xs2, ys2 = load_point_list('/home/whu/Documents/data/17F/2.csv')

markersize_ = 5

plt.plot(xs, ys, '+', markersize=markersize_)
# plt.plot(xs2, ys2, 'x', markersize=markersize_)
# add_text_for_points(pts1, pts2)
add_text_for_points(pts1)
# add_text_for_points(pts1)
plt.show()


# plt.xticks(plt.yticks())

def generate_numpy_array_for_points(pts):
    xs = []
    ys = []
    names = []
    for e in pts:
        xs.append(e.x)
        ys.append(e.y)
        names.append(e.name)
    return np.array(xs), np.array(ys)
