# -*- coding: utf-8 -*-

import cv2
import numpy as np
from sys import argv

import AdaptiveFiltering as AF
import CC
import hulkRemoveKorean

gWidthThr = 1000


def removeNoise(aMat):
    sRows, sCols = aMat.shape[:2]
    # 아마 다른 방식이 있을텐데... 나중에 찾자
    sResultMat = np.zeros([sRows, sCols], dtype=np.float32)
    for row in range(0, sRows):
        for col in range(0, sCols):
            sResultMat.itemset((row, col), 255)

    sCCList = CC.getCC(aMat, 20)

    for sCC in sCCList:
        sPixels = sCC.getPixels()
        for pixel in sPixels:
            px, py = pixel
            sResultMat.itemset((py, px), aMat.item(py, px))
    return sResultMat


def getHangleImg(aMat, aHangleBBList):
    sRows, sCols = aMat.shape[:2]

    sDstMat = np.zeros([sRows, sCols], dtype=np.float32)
    for row in range(0, sRows):
        for col in range(0, sCols):
            sDstMat.itemset((row, col), 255)

    for sRect in aHangleBBList:
        x, y, w, h = sRect
        y = sRows - (y + h)
        for row in range(y, y + h):
            for col in range(x, x + w):
                sDstMat.itemset((row, col), aMat.item(row, col))
    return sDstMat


script, fileName = argv

img = cv2.imread(fileName)

rows, cols = img.shape[:2]

if rows > gWidthThr:
    img = cv2.resize(img, (rows * gWidthThr / rows, cols * gWidthThr / rows), interpolation=cv2.INTER_NEAREST)
img = cv2.fastNlMeansDenoising(img, 7)
img = AF.Optimize(img)
img = removeNoise(img)

blurImg = cv2.blur(img, (90, 1))

sCCList = CC.getCC(blurImg)
sSentenceCnt = 0

for sCC in sCCList:
    x, y, w, h = sCC.getBoundingBox()
    sSentence = img[y:y + h, x:x + w]
    sTreeList, sHangleList = hulkRemoveKorean.removeKorean(sSentence)

    # 수식을 프린트한다.
    for sList in sTreeList:
        sEqStr = ""
        for sTreeNode in sList:
            sEqStr += sTreeNode.__str__
        print sEqStr

    # 한글 이미지를 저장한다.    
    sHangleMat = getHangleImg(sSentence, sHangleList)
    sHFileName = "Sentence" + str(sSentenceCnt) + ".png"
    cv2.imwrite(sHFileName, sHangleMat)
    sSentenceCnt += 1
