import cv2
import numpy as np

img = cv2.imread("/home/whu/Documents/QtProjects/AlphaStarUI/resource/image/2.png")

print(type(img))

# img[:, :, 0] = 255

# cv2.imshow("1", img[:, :, 0])
# cv2.waitKey()

a, b = (1, 2)
print(a, b)

sift = cv2.xfeatures2d.SIFT_create()
