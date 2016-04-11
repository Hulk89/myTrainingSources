# -*- coding: utf-8 -*- 

import numpy as np
from random import shuffle

def softmax_loss_naive(W, X, y, reg):
  """
  Softmax loss function, naive implementation (with loops)

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
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  #############################################################################
  # TODO: Compute the softmax loss and its gradient using explicit loops.     #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  num_train = X.shape[0]
  for i in xrange( num_train ):
    score  = np.dot(X[i,:], W) # i에 대한 class의 score
    score -= np.max(score)    # score의 max값을 빼준다 numerical stability
    Li     = -score[y[i]] + np.log(np.sum(np.exp(score)))
    loss  += Li
    dW[:,y[i]] += -X[i,:].T

    for j in xrange(W.shape[1]):
        dW[:, j] += X[i,:].T * np.exp(score[j]) / np.sum( np.exp(score) )

  loss /= num_train
  dW   /= num_train

  loss += 1/2 * reg * np.sum(W * W)
  dW   += reg * W
  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW


def softmax_loss_vectorized(W, X, y, reg):
  """
  Softmax loss function, vectorized version.

  Inputs and outputs are the same as softmax_loss_naive.
  """
  # Initialize the loss and gradient to zero.
  loss = 0.0
  dW = np.zeros_like(W)

  #############################################################################
  # TODO: Compute the softmax loss and its gradient using no explicit loops.  #
  # Store the loss in loss and the gradient in dW. If you are not careful     #
  # here, it is easy to run into numeric instability. Don't forget the        #
  # regularization!                                                           #
  #############################################################################
  num_train = X.shape[0]
  # score : [N x C]
  #         i-th row - i번째 data에 대한 class score
  score = np.dot(X, W)
  score -= np.max(score)
  # lossY : fy에 해당하는 vector [N x 1]
  lossY = score[np.arange(score.shape[0]),y]
  # expTerm : sum(e^fj) 에 해당하는 vector [N x 1]
  expTerm = np.sum(np.exp(score), axis = 1)
  # logTerm : log취한거 [N x 1]
  logTerm = np.log(expTerm)
  lossVector = logTerm - lossY
  # loss
  loss  += np.sum(lossVector)/num_train

####### gradient ######
  # lossY에 대한 gradient 계산
  dLossY = np.zeros_like(score)
  dLossY[np.arange(X.shape[0]), y] = 1
  dW    -= np.dot(X.T, dLossY)

  # exp term에 대한 gradient 계산
  expX = X.T / expTerm
  dW += np.dot(expX, np.exp(score))

  dW /= num_train

  # regularization term
  loss += 1/2 * reg * np.sum(W * W)
  dW   += reg * W

  #############################################################################
  #                          END OF YOUR CODE                                 #
  #############################################################################

  return loss, dW

