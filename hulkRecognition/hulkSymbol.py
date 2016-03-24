# -*- coding: utf-8 -*-
import hulkSegInfo
from hulkSegInfo import OperType


class hulkSymbol(object):
    gCentroidYFactor = [0.33, 0.66, 0.5]  # ASCENDENT, DESCENDENT, CENTRAL
    gSubThrFactor = [0.2, 0.6, 0.2]
    gSuperThrFactor = [0.8, 0.9, 0.8]

    def __init__(self, aBoundingBox, aClassNum):
        self.mBoundingBox = aBoundingBox
        self.mClassNum = aClassNum

    def setClass(self, aChar):
        self.mClassNum = hulkSegInfo.getClassNum(aChar)

    # Symbol 정보 retrieve
    def getType(self):
        return hulkSegInfo.getSegInfo(self.mClassNum).mOperType

    def getClassNum(self):
        return self.mClassNum

    def getMinX(self):
        return self.mBoundingBox[0]

    def getMaxX(self):
        return self.mBoundingBox[0] + self.mBoundingBox[2]

    def getCentroidY(self):
        sShapeType = hulkSegInfo.getSegInfo(self.mClassNum).mShapeType
        mx, my, mw, mh = self.mBoundingBox

        return my + mh * self.gCentroidYFactor[sShapeType]

    def getCentroidX(self):
        mx, my, mw, mh = self.mBoundingBox
        return mx + mw / 2

    def getSuperThr(self):
        sShapeType = hulkSegInfo.getSegInfo(self.mClassNum).mShapeType
        mx, my, mw, mh = self.mBoundingBox

        return my + mh * self.gSuperThrFactor[sShapeType]

    def getSubThr(self):
        sShapeType = hulkSegInfo.getSegInfo(self.mClassNum).mShapeType
        mx, my, mw, mh = self.mBoundingBox

        return my + mh * self.gSubThrFactor[sShapeType]

    def getWidth(self):
        return self.mBoundingBox[2]

    def getRect(self):
        return self.mBoundingBox

    def getChar(self):
        return hulkSegInfo.getSegInfo(self.mClassNum).mChar

    def getDominateList(self):
        return hulkSegInfo.getSegInfo(self.mClassNum).mDominateList

    def canDominated(self):
        sOperType = hulkSegInfo.getSegInfo(self.mClassNum).mOperType
        if sOperType == OperType.CONSTANT or \
                        sOperType == OperType.VARIABLE or \
                        sOperType == OperType.BRACKETOPEN:
            return True
        else:
            return False

    # 다른 노드와의 관계를 나타내는 함수
    def isLiesInAbove(self, aOtherNode):
        if self.getMinX() <= aOtherNode.getCentroidX() <= self.getMaxX() and \
                        self.getSuperThr() <= aOtherNode.getCentroidY():
            return True
        else:
            return False

    def isLiesInBelow(self, aOtherNode):
        if self.getMinX() <= aOtherNode.getCentroidX() <= self.getMaxX() and \
                        self.getSubThr() >= aOtherNode.getCentroidY():
            return True
        else:
            return False

    def isLiesInUpRight(self, aOtherNode):
        mx, my, mw, mh = self.mBoundingBox
        if self.getMaxX() <= aOtherNode.getCentroidX() and \
                                        self.getCentroidY() + mh / 3 <= aOtherNode.getCentroidY() <= 3 * mh / 2 + my and \
                aOtherNode.canDominated():
            return True
        else:
            return False

    def isLiesInRight(self, aOtherNode):
        return False

    def isLiesInDownRight(self, aOtherNode):
        return False  # BUGBUG

    def isLiesInInside(self, aOtherNode):
        mx, my, mw, mh = self.mBoundingBox
        ax, ay, aw, ah = aOtherNode.mBoundingBox

        if mx <= ax and mx + mw >= ax + aw and my <= aOtherNode.getCentroidY() <= mh + my:
            return True
        else:
            return False

    def isSameBoundingBox(self, aOtherNode):
        x1, y1, w1, h1 = self.mBoundingBox
        x2, y2, w2, h2 = aOtherNode.mBoundingBox

        return x1 == x2 and y1 == y2 and \
               w1 == w2 and h1 == h2

    def isDominate(self, aOtherNode):
        sDominateList = hulkSegInfo.getSegInfo(self.mClassNum).mDominateList
        sDominateType = hulkSegInfo.DominateType.NONE

        if sDominateList[hulkSegInfo.DominateType.UP] and \
                self.isLiesInAbove(aOtherNode):
            sDominateType = hulkSegInfo.DominateType.UP

        if sDominateList[hulkSegInfo.DominateType.DOWN] and \
                self.isLiesInBelow(aOtherNode):
            sDominateType = hulkSegInfo.DominateType.DOWN

        if sDominateList[hulkSegInfo.DominateType.UPRIGHT] and \
                self.isLiesInUpRight(aOtherNode):
            sDominateType = hulkSegInfo.DominateType.UPRIGHT

        if sDominateList[hulkSegInfo.DominateType.INSIDE] and \
                self.isLiesInInside(aOtherNode):
            sDominateType = hulkSegInfo.DominateType.INSIDE

        if sDominateList[hulkSegInfo.DominateType.DOWNRIGHT] and \
                self.isLiesInDownRight(aOtherNode):
            sDominateType = hulkSegInfo.DominateType.DOWNRIGHT

        if sDominateList[hulkSegInfo.DominateType.RIGHT] and \
                self.isLiesInRight(aOtherNode):
            sDominateType = hulkSegInfo.DominateType.RIGHT

        return sDominateType

    def isEqualBoundary(self, aOtherNode):
        mx, my, mw, mh = self.mBoundingBox
        ax, ay, aw, ah = aOtherNode.mBoundingBox

        return mx == ax and my == ay and mw == aw and mh == ah

    def __cmp__(self, aOtherSymbol):
        mx, my, mw, mh = self.mBoundingBox
        ax, ay, aw, ah = aOtherSymbol.mBoundingBox
        if mx < ax:
            return -1
        elif mx > ax:
            return 1
        else:
            return 0

    def __str__(self):
        sChar = hulkSegInfo.getSegInfo(self.mClassNum).mChar
        return "Symbol : %s, BoundingBox : %s" % (sChar, self.mBoundingBox)

    def __repr__(self):
        sChar = hulkSegInfo.getSegInfo(self.mClassNum).mChar
        return "Symbol : %s, BoundingBox : %s" % (sChar, self.mBoundingBox)

