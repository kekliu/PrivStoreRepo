#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np


def odds(p):
    return p / (1 - p)


def odds_inv(p):
    return p / (1 + p)


if __name__ == "__main__":
    arr = np.linspace(0, 0.99, 100)
    plt.plot(arr, odds_inv(odds(arr) * odds(0.55)) - arr, label='$\Delta_{hit}=f_{hit}(p_{old})-p_{old}$')
    plt.plot(arr, odds_inv(odds(arr) * odds(0.49)) - arr, '--', label='$\Delta_{miss}=f_{miss}(p_{old})-p_{old}$')

    plt.xlabel('$p_{old}$')
    plt.ylabel('$\Delta=p_{new}-p_{old}$')

    # 添加图例
    plt.legend(loc='upper right')

    plt.grid()
    plt.show()
    # plt.grid=
