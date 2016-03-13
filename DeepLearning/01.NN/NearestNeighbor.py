# -*- coding: utf-8 -*-
import numpy as np
from dataLoader import load_CIFAR

testNum = 10 # Max : 10000

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
      '''
      L1 Norm
      '''
      #distances = np.sum(np.abs(self.Xtr - X[i,:]), axis = 1)
      ''' 
      L2 Norm
      np.square는 element-wise. 
      axis = 1 > 2번째 axis, 즉 column으로 sum한다.
      '''
      distances = np.sqrt(np.sum(np.square(self.Xtr - X[i,:]), axis = 1))
      min_index = np.argmin(distances) # 가장 작은 distance를 갖는 녀석의 인덱스를 가져옴
      Ypred[i] = self.ytr[min_index] # 위에서 가져온 인덱스로 라벨을 가져옴
 
    return Ypred



Xtr, Ytr, Xte, Yte, sLabels = load_CIFAR()
Xtr_rows = Xtr.reshape(Xtr.shape[0], 32 * 32 * 3) # Xtr_rows는 50000 x 3072
Xte_rows = Xte.reshape(Xte.shape[0], 32 * 32 * 3) # Xte_rows는 10000 x 3072

nn = NearestNeighbor() 

nn.train(Xtr_rows, Ytr) 

Yte_predict = nn.predict(Xte_rows[0:testNum])

print 'accuracy: %f' % ( np.mean(Yte_predict == Yte[0:testNum]) )