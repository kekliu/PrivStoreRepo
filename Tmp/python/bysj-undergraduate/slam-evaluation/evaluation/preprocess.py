#!/usr/bin/env python3
# encoding=utf8

# 本文件的目的是将全站仪的原始文件转换为固定的json格式的文件，
# 然后使用C++自动完成后续的坐标变换和误差评价

import json
import sys
import csv
import datetime


def convert_and_save_all_file_to_json(argv):
    # 遍历所有准备转换的原始文件
    for filename in argv[1:]:
        points = {'points': []}
        with open(filename) as f:
            reader = csv.reader(f)
            data = list(reader)
            for e in data:
                if e[3] == '-': continue
                is_control_point = (True if e[1] == '参考站' else False)
                points['points'].append(
                    {
                        'name': e[0],
                        'is_control_point': is_control_point,
                        'timestamp': datetime.datetime.strptime(e[2], '%m/%d/%Y %H:%M:%S').strftime(
                            '%Y %m %d %H %M %S'),
                        'x': float(e[3]), 'y': float(e[4]), 'z': float(e[6])
                    })
        # 将信息写入json文件，方便C++读取
        with open(filename + '.json', 'w', encoding='utf8') as out_json_file:
            json.dump(points, out_json_file, ensure_ascii=False, indent=2, sort_keys=True)
            print('Formatted data written to "%s.json"' % filename)


if __name__ == '__main__':
    if len(sys.argv) == 1:
        print('usage: ./preprocess.py file1 [file2...]')
        exit(1)
    convert_and_save_all_file_to_json(sys.argv)
