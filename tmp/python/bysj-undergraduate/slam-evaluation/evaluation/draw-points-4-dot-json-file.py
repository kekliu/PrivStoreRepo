#!/usr/bin/env python3

import json
import sys
import math

import matplotlib.pyplot as plt

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('usage: ./exec.py <filename>')
        exit(1)

    # load data
    f = open(sys.argv[1])
    setting = json.load(f)

    if sys.argv[1].__contains__('.json.result'):

        xs_ = []
        ys_ = []
        for e in setting['trajecotry_nodes']:
            xs_.append(float(e['x']))
            ys_.append(float(e['y']))
        plt.plot(xs_, ys_, '-')

        dx = float(setting['transform']['x'])
        dy = float(setting['transform']['y'])
        theta = float(setting['transform']['theta'])

        s = math.sin(theta)
        c = math.cos(theta)

        xs_ = []
        ys_ = []
        for e in setting['points']:
            x1 = float(e['x'])+dx
            y1 = float(e['y'])+dy
            xs_.append(x1 * c + y1 * s)
            ys_.append(y1 * c - x1 * s)
            # plt.text(float(e['x']), float(e['y']), e['name'], fontsize=7)
        plt.plot(xs_, ys_, '+')

    elif sys.argv[1].__contains__('.json'):

        xs_ = []
        ys_ = []
        for e in setting['points']:
            x1 = float(e['x'])
            y1 = float(e['y'])
            xs_.append(x1)
            ys_.append(y1)
            # plt.text(float(e['x']), float(e['y']), e['name'], fontsize=7)
        # plt.plot(xs_, ys_, '+')

    plt.show()
