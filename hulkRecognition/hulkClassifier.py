# -*- coding: utf-8 -*-
from __future__ import division

import os

import cv2
import numpy as np

import hulkHaussdoffDist
import hulkSegInfo


# http://stackoverflow.com/questions/3207219/how-to-list-all-files-of-a-directory-in-python
def list_files(path):
    files = []
    for name in os.listdir(path):
        if os.path.isfile(os.path.join(path, name)):
            files.append(path + name)
    return files

# Note : Img matrix를 주면 point list로 만들어준다.
def makePoint(aMat):
    sPointList = []
    sRows, sCols = aMat.shape[:2]

    for row in range(0, sRows):
        for col in range(0, sCols):
            if aMat.item(row, col) < 127:
                sPointList.append((row, col))
    return sPointList


class hulkClassifier(object):
    gDistanceThr = 10.0
    gRatioThr = 0.1
    # SVM Settings
    mStaticSvm = cv2.SVM()
    mStaticSvm.load("svmData.xml")
    # static Directory for segments
    mStaticDir = "Seg/"

    def __init__(self):
        pass

    def ClassifyBySvm(self, aMat):
        sSegVec = np.zeros([1, 16 * 16], dtype=np.float32)

        sMatResized = cv2.resize(aMat, (16, 16), interpolation=cv2.INTER_NEAREST)

        # print "-START-"
        # for row in range(0, aMat.shape[0]):
        #     for col in range(0, aMat.shape[1]):
        #         print aMat.item(row, col),
        #     print ""
        # print "-aMAT END-"
        # for row in range(0, sMatResized.shape[0]):
        #     for col in range(0, sMatResized.shape[1]):
        #         print sMatResized.item(row, col),
        #     print ""
        # print "-RESIZED-"

        sRows, sCols = sMatResized.shape

        for row in range(0, sRows):
            for col in range(0, sCols):
                # print "row is %s, col is %s" %( row, col )
                sSegVec.itemset((0, 16 * row + col), sMatResized.item(row, col))

        # for row in range(0, sSegVec.shape[0]):
        #     for col in range(0, sSegVec.shape[1]):
        #         print sSegVec.item(row, col),
        #     print ""
        # print "-SVEC END-"

        sClassNum = hulkClassifier.mStaticSvm.predict(sSegVec)

        return int(sClassNum)

    def getMinDistance(self, aMat, aClassNum):
        if hulkSegInfo.getSegInfo(aClassNum).mChar == "-":
            return 0.1
        sFullPath = hulkClassifier.mStaticDir + hulkSegInfo.getSegInfo(aClassNum).mFolder + "/"
        sFiles = list_files(sFullPath)
        sMinDist = 100

        sMatResized = cv2.resize(aMat, (16, 16), interpolation=cv2.INTER_NEAREST)
        sPointList1 = makePoint(sMatResized)

        for file in sFiles:
            if file.endswith(".png"):
                sDstMat = cv2.imread(file, 0)
                sDstMatResized = cv2.resize(sDstMat, (16, 16), interpolation=cv2.INTER_NEAREST)
                sPointList2 = makePoint(sDstMatResized)
                sTmpDist = hulkHaussdoffDist.getDistance(sPointList1, sPointList2)

                if sTmpDist < sMinDist:
                    sMinDist = sTmpDist
                if sMinDist < hulkClassifier.gDistanceThr:
                    break
        return sMinDist

    def isRatioReasonable(self, aMat, aClassNum):
        sRows, sCols = aMat.shape[:2]
        sSrcRatio = sCols / sRows

        # 특별한 심볼들은 먼저 처리해준다.
        if hulkSegInfo.getSegInfo(aClassNum).mChar == "root":
            return True

        if hulkSegInfo.getSegInfo(aClassNum).mChar == "-":
            if sSrcRatio > 1.5:
                return True
            else:
                return False

        if hulkSegInfo.getSegInfo(aClassNum).mChar == ">" or hulkSegInfo.getSegInfo(aClassNum).mChar == "<":
            return True

        sFullPath = hulkClassifier.mStaticDir + hulkSegInfo.getSegInfo(aClassNum).mFolder + "/"
        sFiles = list_files(sFullPath)

        for file in sFiles:
            if file.endswith(".png"):
                sDstMat = cv2.imread(file, 0)
                sDstRows, sDstCols = sDstMat.shape[:2]
                sDstRatio = sDstCols / sDstRows

                if abs(sSrcRatio - sDstRatio) < hulkClassifier.gRatioThr:
                    return True
        return False

    def Classification(self, aMat):
        sClassNum = self.ClassifyBySvm(aMat)

        sDistance = self.getMinDistance(aMat, sClassNum)
        # print sClassNum, sDistance
        if sDistance < hulkClassifier.gDistanceThr and \
                self.isRatioReasonable(aMat, sClassNum):
            return sClassNum
        else:
            return -1


