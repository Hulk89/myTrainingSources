from scipy.misc import imread, imsave, imresize
import matplotlib.pyplot as plt
import numpy as np

# Read an JPEG image into a numpy array
img = imread('assets/drone.jpg')
print img.dtype, img.shape  # Prints "uint8 (400, 248, 3)"

# We can tint the image by scaling each of the color channels
# by a different scalar constant. The image has shape (400, 248, 3);
# we multiply it by the array [1, 0.95, 0.9] of shape (3,);
# numpy broadcasting means that this leaves the red channel unchanged,
# and multiplies the green and blue channels by 0.95 and 0.9
# respectively.
img_tinted = img * [1, 0.95, 0.9]

# Resize the tinted image to be 300 by 300 pixels.
img_tinted = imresize(img_tinted, (300, 300))

plt.subplot( 1,2,1 )
plt.imshow( img )

plt.subplot( 1, 2, 2 )
# A slight gotcha with imshow is that it might give strange results
# if presented with data that is not uint8. To work around this, we
# explicitly cast the image to uint8 before displaying it.
plt.imshow( np.uint8( img_tinted ) )
plt.show()


# Write the tinted image back to disk
imsave('assets/drone_tinted.jpg', img_tinted)

