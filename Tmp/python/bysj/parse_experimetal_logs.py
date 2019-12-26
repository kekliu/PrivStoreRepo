#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 本文件用于解析Cartographer日志，获取时间信息

import re


def parse_one_file(filename):

    file = open(filename)

    the_last_msg = ''
    CPU_line = ''
    RUNTIME_line = ''
    while 1:
        lines = file.readlines(100000)
        if not lines:
            break
        for line in lines:
            if line.__contains__('Total') and line.__contains__('computations resulted in'):
                the_last_msg = line
            elif line.__contains__('Elapsed wall clock time'):
                RUNTIME_line = line
            elif line.__contains__('Elapsed CPU time'):
                CPU_line = line
            pass

    grps = re.search('Total (\d+) computations resulted in (\d+)', the_last_msg)
    grps2 = re.search('Elapsed wall clock time: ([\d.]+)', RUNTIME_line)
    grps3 = re.search('Elapsed CPU time: ([\d.]+)', CPU_line)

    print(grps.group(1), grps.group(2), grps2.group(1), grps3.group(1), sep='\t')


if __name__ == '__main__':
    filename = '/home/whu/Documents/data/slam/cartographer/experiment.log'
    file = open(filename)
    while 1:
        lines = file.readlines(100000)
        if not lines:
            break
        for line in lines:
            if line.__contains__('.ros/log'):
                parse_one_file((line + '/rosout.log').replace('\n', ''))
