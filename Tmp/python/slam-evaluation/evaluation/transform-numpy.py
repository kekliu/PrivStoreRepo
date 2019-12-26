import numpy
import math

data = numpy.matrix([
    [-6.4589, -3.9291, 24.1184, 22.9244],
    # [-7.4473, -3.2421, 23.9164, 21.5218],
    [4.7296, -34.2979, 6.6098, -5.4732],
    [5.4915, -34.8143, 6.6496, -6.4036]
])

# result = [31.1023, 18.8931, 0.924432]
result = numpy.matrix([30.8473, 19.6899, 0.905965])

error = 0

# 写法1
for e in data:
    c = math.cos(result[0, 2])
    s = math.sin(result[0, 2])
    rot = numpy.matrix([[c, s], [-s, c]])
    residual = rot * e[0, 0:2].T + result[0, 0:2].T - e[0, 2:4].T
    print(residual)
    error += residual.T * residual

print('final const:', float(error) / 2)
print('error:', math.sqrt(error / (8 - 3)))

# 写法2
c = math.cos(result[0, 2])
s = math.sin(result[0, 2])
rot = numpy.matrix([[c, s], [-s, c]])
translation = numpy.ones((2, data.shape[0]))
translation[0, :] *= float(result[0, 0])
translation[1, :] *= float(result[0, 1])
residual = rot * data[:, 0:2].T + translation - data[:, 2:4].T
print(residual)
print('final const(2):', numpy.sum(numpy.diag(residual * residual.T)) / 2)
