# Kalman filter example demo in Python

import numpy as np
import matplotlib.pyplot as plt

# plt.rcParams['figure.figsize'] = (10, 8)

# intial parameters
n_iter = 50
sz = (n_iter,)  # size of array
x = 0.37727  # truth value (typo in example at top of p. 13 calls this z)
z = np.random.normal(x, 0.1, size=sz)  # observations (normal about x, sigma=0.1)

Q = 1e-5  # process variance

# allocate space for arrays
xhat = np.zeros(sz)  # a posteri estimate of x
P = np.zeros(sz)  # a posteri error estimate
xhatminus = np.zeros(sz)  # a priori estimate of x
Pminus = np.zeros(sz)  # a priori error estimate
K = np.zeros(sz)  # gain or blending factor

R = 0.1 ** 2  # estimate of measurement variance, change to see effect

# intial guesses
xhat[0] = 0.0
P[0] = 1.0

for k in range(1, n_iter):
    # time update
    xhatminus[k] = xhat[k - 1]
    Pminus[k] = P[k - 1] + Q

    # measurement update
    K[k] = Pminus[k] / (Pminus[k] + R)
    xhat[k] = xhatminus[k] + K[k] * (z[k] - xhatminus[k])
    P[k] = (1 - K[k]) * Pminus[k]

# fig=plt.figure()
fig, leftaxis = plt.subplots()
leftaxis.plot(z, 'k+', label='noisy measurements')
leftaxis.plot(xhat, 'b-', label='a posteri estimate')
leftaxis.axhline(x, color='g', label='truth value')
leftaxis.legend(loc=2)
leftaxis.set_ylabel('Voltage')

right_axis = leftaxis.twinx()
valid_iter = range(1, n_iter)  # Pminus not valid at step 0
right_axis.plot(valid_iter, Pminus[valid_iter], 'y-', label='a priori error estimate')
right_axis.set_ylabel('$Voltage^2$')
right_axis.legend(loc=1)

plt.title('Estimate & Estimated a priori error vs. iteration step', fontweight='bold')
plt.xlabel('Iteration')
plt.setp(plt.gca(), 'ylim', [0, .01])

plt.show()
