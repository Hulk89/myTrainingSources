# -*- coding: utf-8 -*-

import copy
import numpy as np
import CC
import hulkAnalyzer
import hulkClassifier
from hulkSymbol import hulkSymbol


def setSegment(aMat, aCC):
    sPixels = aCC.getPixels()
    x, y, w, h = aCC.getBoundingBox()

    sDst = np.zeros([h, w, 1], dtype=np.float32) # YoungjaeKim (2016-03-09 02:22:39): 3차원일 필요가 있을까? float일 필요가 있을까?

    for row in range(0, h):
        for col in range(0, w):
            sDst.itemset((row, col, 0), 255)

    for pixel in sPixels:
        px, py = pixel
        sDst.itemset((py - y, px - x, 0), aMat.item(py, px))

    return sDst


def valueInRange(aValue, aMin, aMax):
    return aMin <= aValue <= aMax


def isOverlapX(aBB1, aBB2):
    x1, y1, w1, h1 = aBB1
    x2, y2, w2, h2 = aBB2
    sThr1 = w1 / 6
    sThr2 = w2 / 6
    return valueInRange(x1, x2 + sThr2, x2 + w2 - sThr2) or \
           valueInRange(x2, x1 + sThr1, x1 + w1 - sThr1)


def isInside(aBB1, aBB2):
    x1, y1, w1, h1 = aBB1
    x2, y2, w2, h2 = aBB2
    return valueInRange(x1, x2, x2 + w2) and \
           valueInRange(x1 + w1, x2, x2 + w2)


def splitLists(aSymbolList, aHangleBBList):
    sSplitList = []
    sTmpList = []
    sRemainList = copy.copy(aSymbolList)

    for sBB in aHangleBBList:
        x, y, w, h = sBB
        sTmpList = [sSymbol for sSymbol in sRemainList
                    if sSymbol.getMinX() <= x + w]
        sRemainList = [sSymbol for sSymbol in sRemainList
                       if sSymbol.getMinX() > x + w]
        if len(sTmpList) != 0:
            sSplitList.append(copy.copy(sTmpList))

    sSplitList.append(copy.copy(sRemainList))
    return sSplitList


def removeFalseAlarm(aSymbolList, aHangleBBList):
    sSplitList = splitLists(aSymbolList, aHangleBBList)
    sResultList = []
    sHangleList = aHangleBBList;

    for sList in sSplitList:
        sTmpList = []
        for sSymbol in sList:
            sIsOverlapped = False
            for sBB in aHangleBBList:
                sSymbolRect = sSymbol.mBoundingBox
                if isOverlapX(sSymbolRect, sBB) or \
                        (isInside(sSymbolRect, sBB) or isInside(sBB, sSymbolRect)):
                    sIsOverlapped = True
            if not sIsOverlapped:
                sTmpList.append(sSymbol)
            else:
                sHangleList.append(sSymbol.mBoundingBox)
        sResultList.append(copy.copy(sTmpList))

    return sResultList, sHangleList


def removeKorean(aMat):
    sClassifier = hulkClassifier.hulkClassifier()

    sRows, sCols = aMat.shape[:2]
    sCCList = CC.getCC(aMat)

    sSymbolList = []
    sHangleBBList = []

    for sCC in sCCList:
        x, y, w, h = sCC.getBoundingBox()

        if w * h < 30:  # Noise면 건너뛴다.
            continue
        sMat = setSegment(aMat, sCC)
        sClassNum = sClassifier.Classification(sMat)

        if sClassNum != -1:
            sSymbolList.append(hulkSymbol([x, sRows - (y + h), w, h], sClassNum))
        else:
            sHangleBBList.append((x, sRows - (y + h), w, h))

    sSymbolList.sort()
    sHangleBBList.sort()
    sResultList, sHangleList = removeFalseAlarm(sSymbolList, sHangleBBList)
    sTreeList = []
    for sList in sResultList:
        sTreeList.append(hulkAnalyzer.analyze(sList))

    return sTreeList, sHangleList
