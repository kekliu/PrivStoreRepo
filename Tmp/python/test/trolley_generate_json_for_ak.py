#! encoding=utf8

import json
import numpy as np

import tf.transformations as ttr

lines = np.loadtxt('/home/whu/Downloads/ROSDATA_2018-12-14-11-23-40.bag.pbstream.csv', delimiter=', ')

with open("/home/whu/Downloads/IVLocal.json", 'r') as load_f:
    load_dict = json.load(load_f)

H = 1.8

for i in range(0, lines.shape[0]):
    X, Y, Z, x, y, z, w = lines[i][1:]

    has_found = False
    for e in load_dict['poses']:
        if e['id'] == i + 1:
            e['orientation'] = [w, x, y, z]
            e['dataset_location'] = [X, Y, Z]
            e['dataset_floor_location'] = [X, Y, Z - H]

    for e in load_dict['images']:
        if e['id'] == i + 1:
            e['orientation'] = [w, x, y, z]
            e['dataset_location'] = [X, Y, Z]
            e['dataset_floor_location'] = [X, Y, Z - H]

    for e in load_dict['PosesAngleMatrixs']:
        if e['Pose_Id'] == i + 1:
            eulers = ttr.euler_from_quaternion([x, y, z, w])
            e['SenceAngle'] = eulers[2]

    # if not has_found:
    #     print 'ERROR'

with open("/home/whu/Downloads/IVLocal-out.json", "w") as dump_f:
    json.dump(load_dict, dump_f, indent=2, sort_keys=True)
