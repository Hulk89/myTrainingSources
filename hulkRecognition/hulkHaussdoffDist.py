# -*- coding: utf-8 -*-
from __future__ import division
import math


def distance_2(aPointList1, aPointList2):
    maxDist12 = 0.0

    for aPoint1 in aPointList1:
        minB = 1000000.0
        for aPoint2 in aPointList2:
            dx = aPoint1[0] - aPoint2[0]
            dy = aPoint1[1] - aPoint2[1]

            tmpDist = dx * dx + dy * dy

            if tmpDist < minB:
                minB = tmpDist
            if tmpDist == 0.0:
                break
        maxDist12 = maxDist12 + minB
    return maxDist12


# Note      : haussdoff distance를 return 한다.
# Arguments : (x,y)로 된 point의 list 2개
#             ex > [ (1,2),(2,3),... ] 
def getDistance(aPointList1, aPointList2):
    maxDist12 = distance_2(aPointList1, aPointList2)
    maxDist21 = distance_2(aPointList2, aPointList1)
    maxDist = max(maxDist12, maxDist21)

    return math.sqrt(maxDist)


## Test Section
if __name__ == '__main__':
    print "No Test Yet!"
