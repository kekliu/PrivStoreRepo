#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import sys

if len(sys.argv) != 2:
    print('Usage: compute-accuracy.py <pose_graph_filename>')
    exit(1)

pose_graph_filename = sys.argv[1]

if not os.path.exists(pose_graph_filename):
    print('file \'%s\' not found', pose_graph_filename)
    exit(2)

os.system('cartographer_autogenerate_ground_truth' +
          ' -min_covered_distance 40' +
          ' -pose_graph_filename ' + pose_graph_filename +
          ' -output_filename ' + pose_graph_filename + '.ground_truth'
          )

os.system('cartographer_compute_relations_metrics'
          ' -pose_graph_filename ' + pose_graph_filename +
          ' -relations_filename ' + pose_graph_filename + '.ground_truth')
