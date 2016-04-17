import numpy as np
import matplotlib.pyplot as plt

pAxisScale = 5

Data = np.array( [[2.5, 0.5, 2.2, 1.9, 3.1, 2.3, 2, 1, 1.5, 1.1],
         		  [2.4, 0.7, 2.9, 2.2, 3.0, 2.7, 1.6, 1.1, 1.6, 0.9]] )
# The original data
Data = Data.T

# 0-mean data
Data0 = Data - np.mean(Data, axis = 0)

# PCA
numberOfData = Data0.shape[0]
cov = np.dot( Data0.T,Data0 ) / numberOfData 
U,S,V = np.linalg.svd(cov)

print "eigen vectors of cov : "
print U
print "eigen values of cov : "
print S

DataRot = np.dot( Data0, U)

DataO = np.dot( DataRot, U.T)
# plot the data
# http://www.scipy-lectures.org/intro/matplotlib/matplotlib.html

# set size of figure
plt.figure( figsize = (9, 3) )

# plot original data
plt.subplot(1,3,1) 

ax = plt.gca()  # gca stands for 'get current axis'
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))

plt.plot( Data[:,0],Data[:,1], 'ro' )
plt.axis([-pAxisScale,pAxisScale,-pAxisScale,pAxisScale])
plt.title('Original data')

# plot 0-mean data
plt.subplot(1,3,2)

ax = plt.gca()  # gca stands for 'get current axis'
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))

plt.plot( Data0[:,0],Data0[:,1], 'bo' )
plt.axis([-pAxisScale,pAxisScale,-pAxisScale,pAxisScale])
plt.title('0-mean data')

# plot PCA
plt.subplot(1,3,3)

ax = plt.gca()  # gca stands for 'get current axis'
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')
ax.xaxis.set_ticks_position('bottom')
ax.spines['bottom'].set_position(('data',0))
ax.yaxis.set_ticks_position('left')
ax.spines['left'].set_position(('data',0))

plt.plot( DataRot[:,0],DataRot[:,1], 'go' )
plt.axis([-pAxisScale,pAxisScale,-pAxisScale,pAxisScale])
plt.title('PCA data')


# plot final figure
plt.show()