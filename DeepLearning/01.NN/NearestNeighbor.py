# -*- coding: utf-8 -*-
import numpy as np
from dataLoader import load_CIFAR

testNum = 100 # Max : 10000

class NearestNeighbor(object):
  def __init__(self):
    pass

  def train(self, X, y):
    """ 
    X : N x D. 각 Row가 example이다. 
    Y : N x 1. 각 Row가 label이다.
    """
    # Nearest Neighbor는 단순히 training data를 모두 기억한다.
    self.Xtr = X
    self.ytr = y

  def predict(self, X):
    """ 
    X : N x D. 각 Row가 testImage이다.
    """
    num_test = X.shape[0]
    # lets make sure that the output type matches the input type
    Ypred = np.zeros(num_test, dtype = self.ytr.dtype)

    # loop over all test rows
    for i in xrange(num_test):
      # find the nearest training image to the i'th test image
      # using the L1 distance (sum of absolute value differences)
      # distances = np.sum(np.abs(self.Xtr - X[i,:]), axis = 1)
      distances = np.sqrt(np.sum(np.square(self.Xtr - X[i,:]), axis = 1))
      min_index = np.argmin(distances) # get the index with smallest distance
      Ypred[i] = self.ytr[min_index] # predict the label of the nearest example

    return Ypred



Xtr, Ytr, Xte, Yte, sLabels = load_CIFAR()
Xtr_rows = Xtr.reshape(Xtr.shape[0], 32 * 32 * 3) # Xtr_rows becomes 50000 x 3072
Xte_rows = Xte.reshape(Xte.shape[0], 32 * 32 * 3) # Xte_rows becomes 10000 x 3072

nn = NearestNeighbor() # create a Nearest Neighbor classifier class

nn.train(Xtr_rows, Ytr) # train the classifier on the training images and labels

Yte_predict = nn.predict(Xte_rows[0:testNum]) # predict labels on the test images
# and now print the classification accuracy, which is the average number
# of examples that are correctly predicted (i.e. label matches)

print 'accuracy: %f' % ( np.mean(Yte_predict == Yte[0:testNum]) )