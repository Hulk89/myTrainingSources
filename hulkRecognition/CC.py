# -*- coding: utf-8 -*-
import cv2

import AdaptiveFiltering as AF

gNoiseThr = 10


class DisjointSet(object):
    def __init__(self):
        self.mSubsetNum = 0
        self.mDisjointArr = []
        pass

    def __del__(self):
        pass

    def add(self):
        sCurSize = len(self.mDisjointArr)
        self.mDisjointArr.append(sCurSize)
        self.mSubsetNum += 1
        return sCurSize

    def find(self, x):
        if self.mDisjointArr[x] < 0 or self.mDisjointArr[x] == x:
            return x
        else:
            self.mDisjointArr[x] = self.find(self.mDisjointArr[x])
            return self.mDisjointArr[x]

    def unite(self, x, y):
        if x == y:
            return
        xRoot = self.find(x)
        yRoot = self.find(y)

        if xRoot == yRoot:
            return
        elif xRoot < yRoot:
            self.mDisjointArr[yRoot] = xRoot
        else:
            self.mDisjointArr[xRoot] = yRoot

        self.mSubsetNum -= 1

    def getSubsetNum(self):
        return self.mSubsetNum


class ConnectedComponent(object):
    def __init__(self, x=0, y=0):
        if x == 0 and y == 0:
            self.mBoundingBox = (0, 0, 0, 0)
            self.mPixelCount = 0
            self.mPixels = []
        else:
            self.mBoundingBox = (x, y, 1, 1)
            self.mPixelCount = 1
            self.mPixels = [(x, y)]

    def __del__(self):
        pass

    def addPixel(self, x, y):
        self.mPixelCount += 1

        if self.mPixelCount == 0:
            self.mBoundingBox = (x, y, 1, 1)
        else:
            mx, my, mw, mh = self.mBoundingBox

            # 영역 넓히기
            if x < mx:
                mw = mw + mx - x
                mx = x
            elif x > (mx + mw - 1):
                mw = x - mx + 1

            if y < my:
                mh = mh + my - y
                my = y
            elif y > (my + mh - 1):
                mh = y - my + 1

            self.mBoundingBox = (mx, my, mw, mh)

        self.mPixels.append((x, y))

    def getBoundingBoxArea(self):
        mx, my, mw, mh = self.mBoundingBox
        return mw * mh

    def getBoundingBox(self):
        return self.mBoundingBox

    def getPixels(self):
        return self.mPixels


def findCC(aSrcImage):
    sRows, sCols = aSrcImage.shape[:2]

    sCCList = []
    sTotalPix = aSrcImage.size
    sFrameLabel = [0] * sTotalPix  # http://stackoverflow.com/q/983699
    sLabels = DisjointSet()
    sRootMap = [0] * sTotalPix
    sCurIdx = 0

    for y in range(0, sRows):
        for x in range(0, sCols):

            sLeftData = 0
            sUpData = 0

            sLeftIdx = sCurIdx - 1
            sUpIdx = sCurIdx - sCols

            if x == 0:
                sLeftData = 0
            else:
                sLeftData = aSrcImage.item(y, x - 1)

            if y == 0:
                sUpData = 0
            else:
                sUpData = aSrcImage.item(y - 1, x)

            sCurData = aSrcImage.item(y, x)

            if sCurData > 0:
                if sLeftData == 0 and sUpData == 0:
                    sFrameLabel[sCurIdx] = sLabels.add()
                    sRootMap[sFrameLabel[sCurIdx]] = -1

                elif sLeftData != 0 and sUpData == 0:
                    sFrameLabel[sCurIdx] = sFrameLabel[sLeftIdx]

                elif sUpData != 0 and sLeftData == 0:
                    sFrameLabel[sCurIdx] = sFrameLabel[sUpIdx]

                else:
                    if sFrameLabel[sLeftIdx] > sFrameLabel[sUpIdx]:
                        sFrameLabel[sCurIdx] = sFrameLabel[sUpIdx]
                    else:
                        sFrameLabel[sCurIdx] = sFrameLabel[sLeftIdx]

                    sLabels.unite(sFrameLabel[sLeftIdx], sFrameLabel[sUpIdx])
            else:
                sFrameLabel[sCurIdx] = -1

            sCurIdx += 1

    sCurIdx = 0
    sCurLabel = 0
    sConnCompIdx = 0

    for y in range(0, sRows):
        for x in range(0, sCols):
            sCurLabel = sFrameLabel[sCurIdx]

            if sCurLabel != -1:
                sCurLabel = sLabels.find(sCurLabel)

                if sRootMap[sCurLabel] != -1:
                    sCCList[sRootMap[sCurLabel]].addPixel(x, y)
                else:
                    sCCList.append(ConnectedComponent(x, y))
                    sRootMap[sCurLabel] = sConnCompIdx
                    sConnCompIdx += 1
            sCurIdx += 1

    return sCCList


"""
픽셀개수가 노이즈로 정의한 갯수보다 큰 것만 반환한다
"""
def getCC(aSrcImage, aNoiseThr=gNoiseThr):
    sSrcImage = 255 - aSrcImage
    return [sCC for sCC in findCC(sSrcImage) if sCC.getPixels().__len__() > aNoiseThr]


## Test Section
if __name__ == '__main__':

    # Test CC
    cc = ConnectedComponent()
    cc.addPixel(1, 2)
    print cc.getBoundingBox()
    print cc.getBoundingBoxArea()
    print cc.getPixels()

    # Test findCC
    img = cv2.imread('Images/test.png')

    img = AF.Optimize(img)

    sCCList = getCC(img)

    print len(sCCList)

    ccImg = cv2.cvtColor(img, cv2.COLOR_GRAY2RGB)
    for CC in sCCList:
        x, y, w, h = CC.getBoundingBox()
        cv2.rectangle(ccImg, (x, y), (x + w, y + h), (255, 0, 0), 1)
        for pixel in CC.getPixels():
            ccImg.itemset((pixel[1], pixel[0], 2), 255)
    cv2.imshow("ccImage", ccImg)
    cv2.waitKey(0)
