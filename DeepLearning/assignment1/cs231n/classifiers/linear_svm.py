# -*- coding: utf-8 -*- 

import numpy as np
from random import shuffle

def svm_loss_naive(W, X, y, reg):
  """
  Structured SVM loss function, naive implementation (with loops).

  Inputs have dimension D, there are C classes, and we operate on minibatches
  of N examples.

  Inputs:
  - W: A numpy array of shape (D, C) containing weights.
  - X: A numpy array of shape (N, D) containing a minibatch of data.
  - y: A numpy array of shape (N,) containing training labels; y[i] = c means
    that X[i] has label c, where 0 <= c < C.
  - reg: (float) regularization strength

  Returns a tuple of:
  - loss as single float
  - gradient with respect to weights W; an array of same shape as W
  """
  dW = np.zeros(W.shape) # initialize the gradient as zero

  # compute the loss and the gradient
  num_classes = W.shape[1]
  num_train = X.shape[0]
  loss = 0.0
  for i in xrange(num_train):
    scores = X[i].dot(W)
    correct_class_score = scores[y[i]]
    for j in xrange(num_classes):
      if j == y[i]:
        continue
      margin = scores[j] - correct_class_score + 1 # note delta = 1
      if margin > 0:
        loss += margin
        # loss에 max(0, term)에서 term이 더해진다는 말은 gradient도 term에서 나온다는 말!
        # 따라서 이 때만 gradient를 구해주면 된다.
        dW[:,j] += X[i,:].T
        dW[:,y[i]] -= X[i,:].T

  # Right now the loss is a sum over all training examples, but we want it
  # to be an average instead so we divide by num_train.
  loss /= num_train
  # 여기서도 똑같이 1/N을 해준다.
  dW /= num_train

  # Add regularization to the loss.
  loss += 0.5 * reg * np.sum(W * W)
  
  dW += reg * W
  #############################################################################
  # TODO:                                                                     #
  # Compute the gradient of the loss function and store it dW.                #
  # Rather that first computing the loss and then computing the derivative,   #
  # it may be simpler to compute the derivative at the same time that the     #
  # loss is being computed. As a result you may need to modify some of the    #
  # code above to compute the gradient.                                       #
  #############################################################################


  return loss, dW


def svm_loss_vectorized(W, X, y, reg):
  """
  Structured SVM loss function, vectorized implementation.

  Inputs and outputs are the same as svm_loss_naive.
  """
  loss = 0.0
  dW = np.zeros(W.shape) # initialize the gradient as zero

  #############################################################################
  # TODO:                                                                     #
  # Implement a vectorized version of the structured SVM loss, storing the    #
  # result in loss.                                                           #
  #############################################################################
  num_train  = X.shape[0]
  # scores[i] : i번째 data의 score가 [1xC]로 나옴
  # scores : [N x C]
  scores     = np.dot(X,W) 
  # np.arange( num ) : 0~num-1까지 array를 만들어줌
  # correctScore : [N x 1]이며 각 행에는 correct score를 담고있음
  correctScore = scores[np.arange(scores.shape[0]), y]
  # corrScoreMat : [N x D]이며 correctScore를 broadcast하기 위해 이렇게 함
  corrScoreMat = np.ones( scores.T.shape ) * correctScore.T
  corrScoreMat = corrScoreMat.T
  # margins : 1로 정했지...
  margins = np.ones( scores.shape )
  
  # loss 계산 
  L = scores - corrScoreMat + margins
  # y인 부분은 0으로 세팅...
  L[np.arange( scores.shape[0] ), y] = 0
  # margin보다 큰 경우 무시
  L[ L < 0 ] = 0
  # 다 더하고 train 갯수로 나눔
  loss = np.sum(L)/num_train
  # regularization term
  loss += 0.5 * reg * np.sum(W * W)

  #############################################################################
  #                             END OF YOUR CODE                              #
  #############################################################################

  #############################################################################
  # TODO:                                                                     #
  # Implement a vectorized version of the gradient for the structured SVM     #
  # loss, storing the result in dW.                                           #
  #                                                                           #
  # Hint: Instead of computing the gradient from scratch, it may be easier    #
  # to reuse some of the intermediate values that you used to compute the     #
  # loss.                                                                     #
  #############################################################################
  L = scores - corrScoreMat + margins
  # y인 부분은 0으로 세팅
  L[np.arange(scores.shape[0]), y] = 0
  # y가 아닌데 margin이 넘어가면 0, 아니면 1 세팅
  L[L > 0] = 1
  L[L < 0] = 0
  # 이제 margin이 안넘어간 갯수를 세아리자
  sumOfLoss = np.sum(L, axis = 1)
  # Xyi 는 sumOfLoss만큼 빼야지
  L[np.arange(scores.shape[0]), y] = -1*sumOfLoss
  # 여기까지 하면 L은 다음과 같아진다
  '''
  L = [N x C]이며
  각 행에는 다음과 같은 정보가 주어짐
  
  j != yi이면
    margin을 못넘었을 경우 1
               넘을 경우 0
  j == yi이면
    margin 못넘은 갯수 * -1
  '''
  # 이제 X.T * L / num_train 을 하면 data loss에 대한 계산을 함
  dW += np.dot(X.T, L) / num_train

  # regularization term
  dW += reg * W
  #############################################################################
  #                             END OF YOUR CODE                              #
  #############################################################################

  return loss, dW
