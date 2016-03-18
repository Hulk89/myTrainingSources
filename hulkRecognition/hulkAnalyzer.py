# -*- coding: utf-8 -*-

import copy

from hulkSegInfo import DominateType
from hulkTreeNode import hulkTreeNode

gWidthThr = 3

def matchEq(aSymbol, aList):
    index = -1

    for i in range(0, len(aList)):
        if not aSymbol.isSameBoundingBox(aList[i]):
            if (aSymbol.isLiesInAbove(aList[i]) or aSymbol.isLiesInBelow(aList[i])) and \
                    (abs(aSymbol.getWidth() - aList[i].getWidth()) <= gWidthThr):
                if aList[i].getChar() == "-":
                    index = i
                    break
    return index


def matchDiv(aSymbol, aList):
    sHaveUp = False
    sHaveDown = False

    for sSymbol in aList:
        if not aSymbol.isSameBoundingBox(sSymbol):
            if aSymbol.isLiesInAbove(sSymbol):
                sHaveUp = True
            if aSymbol.isLiesInBelow(sSymbol):
                sHaveDown = True

    return sHaveDown and sHaveUp


def replaceSymbol(aSymbolList):
    sCandidates = ["-", "<", ">", "+"]
    sChangeList = []
    sResultList = []

    for symbol in aSymbolList:
        sChar = symbol.getChar()
        if sChar in sCandidates:
            sChangeList.append(symbol)
        else:
            sResultList.append(symbol)

    '''
    0 : not checked
    1 : checked
    2 : removed
    '''
    sBitmap = [0] * len(sChangeList)

    for i in range(0, len(sChangeList)):
        if sBitmap[i] == 0:
            sSymbol = sChangeList[i]
            sChar = sSymbol.getChar()
            if sChar == "-":
                index = matchEq(sSymbol, sChangeList)
                if index != -1:
                    sChangeList[i].setClass("=")
                    sBitmap[i] = 1
                    sBitmap[index] = 2
                elif matchDiv(sSymbol, aSymbolList):
                    sChangeList[i].setClass("/")
                    sBitmap[i] = 1
                else:
                    sBitmap[i] = 1
            elif sChar == "+":
                index = matchEq(sSymbol, sChangeList)
                if index != -1:
                    sChangeList[i].setClass("+-")
                    sBitmap[i] = 1
                    sBitmap[index] = 2
                else:
                    sBitmap[i] = 1
            elif sChar == ">":
                index = matchEq(sSymbol, sChangeList)
                if index != -1:
                    sChangeList[i].setClass(">=")
                    sBitmap[i] = 1
                    sBitmap[index] = 2
                else:
                    sBitmap[i] = 1
            elif sChar == "<":
                index = matchEq(sSymbol, sChangeList)
                if index != -1:
                    sChangeList[i].setClass("<=")
                    sBitmap[i] = 1
                    sBitmap[index] = 2
                else:
                    sBitmap[i] = 1
            else:
                print "sChangeList component : -,+,<,>"
                assert 0
                pass
        else:
            continue

    for i in range(0, len(sChangeList)):
        if sBitmap[i] == 1:
            sResultList.append(sChangeList[i])
    return sResultList


def getDominantSymbol(aList):
    if len(aList) == 1:
        return aList[0]
    else:
        sResultList = aList[0: len(aList) - 2]
        sLastNode = aList[len(aList) - 1]
        sPrevLastNode = aList[len(aList) - 2]

        if sLastNode.isDominate(sPrevLastNode) != DominateType.NONE:
            sResultList.append(sLastNode)
        else:
            sResultList.append(sPrevLastNode)

        return getDominantSymbol(sResultList)


def getRightNeighbors(aSymbol, aList):
    sNeighborList = []

    for symbol in aList:
        if aSymbol.getMinX() < symbol.getMinX():
            sNeighborList.append(symbol)

    return sNeighborList


def erase(aList, aSymbol):
    for i in range(0, len(aList)):
        if aList[i].isSameBoundingBox(aSymbol):
            del aList[i]
            break


def getListFromTree(aTree):
    sList = []

    for treeNode in aTree:
        sList.append(treeNode.mHulkSymbol)
    return sList


def getFirstSementic(aTree, aList):
    sTreeNode = hulkTreeNode()

    if len(aTree) == 0:
        sTreeNode.mHulkSymbol = getDominantSymbol(aList)
        aTree.append(copy.copy(sTreeNode))

    sLastDomNode = aTree[len(aTree) - 1]

    sRightNeighbors = getRightNeighbors(sLastDomNode.mHulkSymbol, aList)

    if len(sRightNeighbors) == 0:
        return

    sDomNeighbor = getDominantSymbol(sRightNeighbors)

    sDomType = sLastDomNode.mHulkSymbol.isDominate(sDomNeighbor)

    if sDomType != DominateType.NONE:
        erase(aList, sDomNeighbor)

        sTreeNode.clearSubNode()
        sTreeNode.mHulkSymbol = sDomNeighbor
        sLastDomNode.appendToSubTree(sTreeNode, sDomType)
    else:
        sTreeNode.clearSubNode()
        sTreeNode.mHulkSymbol = sDomNeighbor
        aTree.append(sTreeNode)

    getFirstSementic(aTree, aList)


def iterateSementic(aTree):
    for i in range(0, len(aTree)):
        for j in range(0, 6):
            sList = getListFromTree(aTree[i].mSubTree[j])
            sNextList = []
            if len(sList) != 0:
                aTree[i].mSubTree[j] = []
                getFirstSementic(aTree[i].mSubTree[j], sList)
                sNextList = getListFromTree(aTree[i].mSubTree[j])

                if len(sList) == len(sNextList):
                    iterateSementic(aTree[i].mSubTree[j])


def analyze(aSymbolList):
    if len(aSymbolList) == 0:
        return []

    sReplacedSymbolList = replaceSymbol(aSymbolList)
    sReplacedSymbolList.sort()

    sTreeList = []
    getFirstSementic(sTreeList, sReplacedSymbolList)
    iterateSementic(sTreeList)

    return sTreeList

