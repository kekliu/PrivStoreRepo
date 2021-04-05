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
                is_control_point = (True if e[1] == '参考站' else False)
                ymd = str(e[4]).split('.')
                hms = str(e[5]).split(':')
                points['points'].append(
                    {
                        'name': e[0],
                        'is_control_point': is_control_point,
                        'timestamp': str.format('%s %s %s %s %s %s' % (
                            ymd[2], ymd[1], ymd[0], hms[0], hms[1], hms[2])),
                        'x': float(e[2]), 'y': float(e[1]), 'z': float(e[3])
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

result = {
    "x": "-1038.4655011390017",
    "y": "-1002.3587916556534",
    "theta": "2.9028979550356812",
    "delta_time": "621355966998316544"
}
