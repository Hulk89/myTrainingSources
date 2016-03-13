import numpy as np
import matplotlib.pyplot as plt



x = np.arange(0, 3 * np.pi, 0.1)
print x
y = np.sin(x)

plt.plot(x, y)
plt.show()  # You must call plt.show() to make graphics appear.