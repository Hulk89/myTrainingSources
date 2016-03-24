# -*- coding: utf-8 -*-

from hulkSegInfo import DominateType


class hulkTreeNode(object):
    def __init__(self, aHulkSymbol=None):
        if aHulkSymbol is None:
            aHulkSymbol = []
        self.clearSubNode()
        self.mHulkSymbol = aHulkSymbol

    def clearSubNode(self):
        self.mSubTree = [[], [], [], [], [], []]

    # [UP,DOWN,INSIDE,RIGHT,UPRIGHT,DOWNRIGHT]
    def appendToSubTree(self, aTreeNode, aDomType):
        self.mSubTree[aDomType].append(aTreeNode)

    def getSubTree(self, aSubTree):
        aStr = ""
        if len(aSubTree) > 1:
            aStr = "("

        for node in aSubTree:
            aStr += node.__str__

        if len(aSubTree) > 1:
            aStr += ")"
        return aStr

    @property
    def __str__(self):
        aStr = ""

        if len(self.mSubTree[DominateType.UP]) != 0:
            aStr = "\\frac{"
            aStr = aStr + self.getSubTree(self.mSubTree[DominateType.UP])
            aStr += "}"

        sChar = self.mHulkSymbol.getChar()

        if sChar == "!=":
            aStr += "\\neq"
        elif sChar == "<=":
            aStr += "\\le"
        elif sChar == ">=":
            aStr += "\\ge"
        elif sChar == "root":
            aStr += "\\sqrt"
        elif sChar == "pi":
            aStr += "\\pi"
        elif sChar == "*":
            aStr += "\\times"
        elif sChar == "/":
            pass
        else:
            aStr = aStr + sChar

        if len(self.mSubTree[DominateType.DOWNRIGHT]) != 0:
            aStr += "_{"
            aStr = aStr + self.getSubTree(self.mSubTree[DominateType.DOWNRIGHT]).__str__()
            aStr += "}"

        if len(self.mSubTree[DominateType.UPRIGHT]) != 0:
            aStr += "^{"
            aStr = aStr + self.getSubTree(self.mSubTree[DominateType.UPRIGHT]).__str__()
            aStr += "}"

        if len(self.mSubTree[DominateType.RIGHT]) != 0:
            aStr = aStr + self.getSubTree(self.mSubTree[DominateType.RIGHT]).__str__()

        if len(self.mSubTree[DominateType.DOWN]) != 0:
            aStr += "{"
            aStr = aStr + self.getSubTree(self.mSubTree[DominateType.DOWN]).__str__()
            aStr += "}"

        if len(self.mSubTree[DominateType.INSIDE]) != 0:
            aStr += "{"
            aStr = aStr + self.getSubTree(self.mSubTree[DominateType.INSIDE]).__str__()
            aStr += "}"
        return aStr

    def __cmp__(self, aOtherTreeNode):
        if self.mHulkSymbol < aOtherTreeNode.mHulkSymbol:
            return -1
        elif self.mHulkSymbol > aOtherTreeNode.mHulkSymbol:
            return 1
        else:
            return 0


## Test Section
if __name__ == '__main__':
    print "No Test Yet!"
