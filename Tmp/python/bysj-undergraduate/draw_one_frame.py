#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 本脚本用来绘制单个扫描帧直线提取的过程

import matplotlib.pyplot as plt
import numpy

# 添加中文字体支持
import matplotlib.pylab

cnfont = matplotlib.font_manager.FontProperties(fname='/home/whu/font/msyh.ttf')
matplotlib.pylab.mpl.rcParams['axes.unicode_minus'] = False

# 公共全局变量
points_ = None
sparse_line_indexs_ = None
sparse_line_points_ = None
line_indexs_ = None
line_points_ = None


def generate_points_from_ranges(ranges):
    global points_
    min_angle = -2.356194
    angle_increment = 0.004363
    delta_angle = numpy.mat(range(ranges.size)).T * angle_increment
    x = numpy.multiply(ranges, numpy.cos(min_angle + delta_angle))
    y = numpy.multiply(ranges, numpy.sin(min_angle + delta_angle))
    points_ = numpy.hstack((x, y))
    pass


def parse_one_frame_file(frame_id):
    global sparse_line_indexs_, sparse_line_points_, line_indexs_, line_points_
    file = open('/home/whu/data/' + frame_id.__str__())

    line = file.readline().rstrip()
    ranges = numpy.mat([float(x) for x in line.split(' ')]).T
    generate_points_from_ranges(ranges)
    line = file.readline().rstrip()
    sparse_line_indexs_ = numpy.mat([int(x) for x in line.split(' ')]).reshape((-1, 2))
    line = file.readline().rstrip()
    sparse_line_points_ = numpy.mat([float(x) for x in line.split(' ')]).reshape((-1, 4))
    line = file.readline().rstrip()
    line_indexs_ = numpy.mat([int(x) for x in line.split(' ')]).reshape((-1, 2))
    line = file.readline().rstrip()
    line_points_ = numpy.mat([float(x) for x in line.split(' ')]).reshape((-1, 4))

    pass


def draw_colored_point_clouds(axs, line_indexs):
    colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']
    cur_index = 0
    for pt in line_indexs:
        ptcld = points_[pt[0, 0]:pt[0, 1], :]
        axs.plot(ptcld[:, 0], ptcld[:, 1], colors[cur_index] + '.', markersize=0.3)
        cur_index = (cur_index + 1) % colors.__len__()
    pass


def draw_colored_lines(axs, line_points):
    for l in line_points:
        axs.plot([l[0, 0], l[0, 2]], [l[0, 1], l[0, 3]], '#000000', linewidth=1)
    pass


def draw(frame_id):
    parse_one_frame_file(frame_id)

    # 此处有bug，若设sharex为True，则axis('equal')时无法显示全部的图
    fig, axs = plt.subplots(2, 2)

    axs[0, 0].axis('equal')
    axs[0, 1].axis('equal')
    axs[1, 0].axis('equal')
    axs[1, 1].axis('equal')

    axs[0, 0].plot(points_[:, 0], points_[:, 1], '.', markersize=0.5)
    # 注意，若这样做，则返回的xlim,ylim,axis都是错的
    axs[0, 0].set_title(u'原始激光点云', fontproperties=cnfont)

    draw_colored_point_clouds(axs[0, 1], sparse_line_indexs_)
    axs[0, 1].set_title(u'预处理和区域分割后的点云', fontproperties=cnfont)

    draw_colored_point_clouds(axs[1, 0], sparse_line_indexs_)
    draw_colored_lines(axs[1, 0], sparse_line_points_)
    axs[1, 0].set_title(u'线段拟合', fontproperties=cnfont)

    draw_colored_point_clouds(axs[1, 1], line_indexs_)
    draw_colored_lines(axs[1, 1], line_points_)
    axs[1, 1].set_title(u'线段拼接', fontproperties=cnfont)

    fig.savefig('data/' + frame_id.__str__())
    # plt.show()
    plt.close(fig)
    pass


# 设置输出的图片大小为 9600px X 7200px
matplotlib.pylab.rcParams['figure.figsize'] = 9.6, 7.2
# draw(5300)
for i in range(0, 5410, 30):
    draw(i)
    print(i)
