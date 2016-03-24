# -*- coding: utf-8 -*-

from hulkSymbol import hulkSymbol
import unittest
import hulkAnalyzer
import copy

class hulkAnalyzerTest( unittest.TestCase ):
    # A = ~~~
    def setUp(self):
        self.mSymbolList = [ hulkSymbol([5, 14, 29, 29], 20),\
                    hulkSymbol([38, 29, 28, 3], 44),\
                    hulkSymbol([71, 8, 121, 42], 38),\
                    hulkSymbol([94, 8, 9, 36], 0),\
                    hulkSymbol([111, 25, 27, 3], 4),\
                    hulkSymbol([142, 14, 16, 26], 9),\
                    hulkSymbol([161, 8, 10, 36], 1),\
                    hulkSymbol([175, 31, 10, 15], 7) ]
    
    # 먼저 symbol이 바뀌지 않았는지 알아야한다.
    def testSymbolList( self ):
        sStr = ""
        for sSymbol in self.mSymbolList:
            sStr = sStr + sSymbol.getChar()
        
        self.assertEqual( sStr, "A=root(-4)2" )

    # Root와의 관계만 들어가고 아직 제곱은 없어야한다.
    def testGetFirstSementic( self ):
        sTreeList = []
        hulkAnalyzer.getFirstSementic( sTreeList, self.mSymbolList)
        sStr = ""
        for sTreeNode in sTreeList:
            sStr = sStr + sTreeNode.__str__
        self.assertEqual( sStr, "A=\sqrt{((-4)2)}" )

    # iterateSementic을 돌면 제곱도 들어가야한다.
    def testIterateSementic( self ):
        sTreeList = []
        hulkAnalyzer.getFirstSementic( sTreeList, self.mSymbolList)
        hulkAnalyzer.iterateSementic( sTreeList )
        sStr = ""
        for sTreeNode in sTreeList:
            sStr = sStr + sTreeNode.__str__
        self.assertEqual( sStr, "A=\sqrt{((-4)^{2})}" )

if __name__ == '__main__':
    TS = unittest.makeSuite( hulkAnalyzerTest,"test")
    runner = unittest.TextTestRunner()
    runner.run(TS)
