# -*- coding: utf-8 -*-


class ShapeType:
    def __init__(self):
        pass

    ASCENDENT, DESCENDENT, CENTRAL = range(3)


class OperType:
    def __init__(self):
        pass

    CONSTANT, VARIABLE, BRACKETOPEN, BRACKETCLOSE, OTHERS = range(5)


class DominateType:
    def __init__(self):
        pass

    UP, DOWN, INSIDE, RIGHT, UPRIGHT, DOWNRIGHT, NONE = range(7)


class hulkSegInfo(object):
    def __init__(self, aChar, aFolder, aDominateList, aShapeType, aOperType):
        self.mChar = aChar
        self.mFolder = aFolder
        self.mDominateList = aDominateList
        self.mShapeType = aShapeType
        self.mOperType = aOperType


gInfoList = [
    # mChar, mFolder, [UP,DOWN,INSIDE,RIGHT,UPRIGHT,DOWNRIGHT]
    hulkSegInfo("a", "_a", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("b", "_b", [0, 0, 0, 1, 1, 1], ShapeType.ASCENDENT, OperType.VARIABLE),
    hulkSegInfo("c", "_c", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("d", "_d", [0, 0, 0, 1, 1, 1], ShapeType.ASCENDENT, OperType.VARIABLE),
    hulkSegInfo("m", "_m", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("n", "_n", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("p", "_p", [0, 0, 0, 1, 1, 1], ShapeType.DESCENDENT, OperType.VARIABLE),
    hulkSegInfo("q", "_q", [0, 0, 0, 1, 1, 1], ShapeType.DESCENDENT, OperType.VARIABLE),
    hulkSegInfo("pi", "_pi", [0, 0, 0, 1, 1, 1], ShapeType.DESCENDENT, OperType.VARIABLE),
    hulkSegInfo("x", "_x", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("y", "_y", [0, 0, 0, 1, 1, 1], ShapeType.DESCENDENT, OperType.VARIABLE),
    hulkSegInfo("z", "_z", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("A", "_AA", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("B", "_BB", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("D", "_DD", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("E", "_EE", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("F", "_FF", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("G", "_GG", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("H", "_HH", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("P", "_PP", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("Q", "_QQ", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("R", "_RR", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("S", "_SS", [0, 0, 0, 1, 1, 1], ShapeType.CENTRAL, OperType.VARIABLE),
    hulkSegInfo("0", "_0", [0, 0, 0, 0, 1, 0], ShapeType.CENTRAL, OperType.CONSTANT),
    hulkSegInfo("1", "_1", [0, 0, 0, 1, 1, 0], ShapeType.CENTRAL, OperType.CONSTANT),
    hulkSegInfo("2", "_2", [0, 0, 0, 1, 1, 0], ShapeType.CENTRAL, OperType.CONSTANT),
    hulkSegInfo("3", "_3", [0, 0, 0, 1, 1, 0], ShapeType.CENTRAL, OperType.CONSTANT),
    hulkSegInfo("4", "_4", [0, 0, 0, 1, 1, 0], ShapeType.CENTRAL, OperType.CONSTANT),
    hulkSegInfo("5", "_5", [0, 0, 0, 1, 1, 0], ShapeType.CENTRAL, OperType.CONSTANT),
    hulkSegInfo("6", "_6", [0, 0, 0, 1, 1, 0], ShapeType.CENTRAL, OperType.CONSTANT),
    hulkSegInfo("7", "_7", [0, 0, 0, 1, 1, 0], ShapeType.CENTRAL, OperType.CONSTANT),
    hulkSegInfo("8", "_8", [0, 0, 0, 1, 1, 0], ShapeType.CENTRAL, OperType.CONSTANT),
    hulkSegInfo("9", "_9", [0, 0, 0, 1, 1, 0], ShapeType.CENTRAL, OperType.CONSTANT),
    hulkSegInfo("(", "_left_bracket", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.BRACKETOPEN),
    hulkSegInfo("[", "_left_squarebracket", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.BRACKETOPEN),
    hulkSegInfo(")", "_right_bracket", [0, 0, 0, 0, 1, 0], ShapeType.CENTRAL, OperType.BRACKETCLOSE),
    hulkSegInfo("]", "_right_squarebracket", [0, 0, 0, 0, 1, 0], ShapeType.CENTRAL, OperType.BRACKETCLOSE),
    hulkSegInfo("+", "_plus", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo("-", "_minus", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo("+-", "_pm", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo("*", "_mult", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo(">", "_greater", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo("<", "_less", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo(">=", "_greater_equal", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo("<=", "_less_equal", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo("/", "_div", [1, 1, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo("=", "_equal", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo("!=", "_not_equal", [0, 0, 0, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS),
    hulkSegInfo("root", "_root", [0, 0, 1, 0, 0, 0], ShapeType.CENTRAL, OperType.OTHERS)]

gInfoListSorted = []


def sortInfoList():
    if len(gInfoListSorted) != 0:
        print "redundant sort. clear up."
        for item in gInfoListSorted:
            del item
    classListFile = open("class.list")

    lines = [line.rstrip() for line in classListFile]  # return을 지운다.

    for line in lines:
        classListData = line.split(" : ")
        for segType in gInfoList:
            if segType.mFolder == classListData[0]:
                gInfoListSorted.append(segType)
                break
    classListFile.close()


def getSegInfo(aClassNum):
    return gInfoListSorted[aClassNum]


def getClassNum(aChar):
    for i in range(0, len(gInfoListSorted)):
        if gInfoListSorted[i].mChar == aChar:
            return i
    return -1


sortInfoList()

## Test Section
if __name__ == '__main__':
    # Test Enum
    x = ShapeType.ASCENDENT
    if x == ShapeType.ASCENDENT:
        print "alright"
        print x
    else:
        print x

    # Test hulkSegInfo
    print gInfoList[0].mOperType

    # TestSorting

    sortInfoList()

    for i in range(0, len(gInfoListSorted)):
        print "[" + str(i) + "]" + "mChar : " + gInfoListSorted[i].mChar
    print "--------------------class num = 0--------------------"
    print getSegInfo(0).mChar
    print getSegInfo(0).mFolder
    print getSegInfo(0).mDominateList[DominateType.UP]
    print getSegInfo(0).mDominateList[DominateType.DOWN]
    print getSegInfo(0).mDominateList[DominateType.INSIDE]
    print getSegInfo(0).mDominateList[DominateType.RIGHT]
    print getSegInfo(0).mDominateList[DominateType.UPRIGHT]
    print getSegInfo(0).mDominateList[DominateType.DOWNRIGHT]
    print getSegInfo(0).mShapeType
    print getSegInfo(0).mOperType
