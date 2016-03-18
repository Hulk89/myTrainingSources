from hulkSymbol import hulkSymbol
from hulkSegInfo import DominateType
import unittest

class hulkSymbolTest( unittest.TestCase ):
    def testCompareSymbol( self ):
        # x^2 + y. ClassNum can be changed when new training comes.
        sSymbolX = hulkSymbol([0, 0, 8, 8], 41)
        sSymbol2 = hulkSymbol([11, 8, 3, 4], 7)
        sSymbolPlus = hulkSymbol([12, 0, 10, 10], 3)
        sSymbolY = hulkSymbol([24, 0, 8, 10], 42)

        sSymbolList = [sSymbolX, sSymbolY, sSymbolPlus, sSymbol2]

        sSymbolListSorted = sorted(sSymbolList)
        sExpectesList = [sSymbolX,sSymbol2,sSymbolPlus, sSymbolY]
        
        for i in range( 0, len( sSymbolListSorted ) ):
            self.assertEqual( id(sSymbolListSorted[i]), id(sExpectesList[i]) )
        
    def testIsLiesInUpRight( self ):
        # x^2
        sSymbolX = hulkSymbol([0, 0, 8, 8], 41)
        sSymbol2 = hulkSymbol([11, 8, 3, 4], 7)

        self.assertTrue( sSymbolX.isLiesInUpRight(sSymbol2) )

    def testIsDominate( self ):
        # x^2
        sSymbolX = hulkSymbol([0, 0, 8, 8], 41)
        sSymbol2 = hulkSymbol([11, 8, 3, 4], 7)
        
        self.assertNotEqual( sSymbolX.isDominate(sSymbol2), DominateType.NONE )
        
if __name__ == '__main__':
    TS = unittest.makeSuite( hulkSymbolTest,"test")
    runner = unittest.TextTestRunner()
    runner.run(TS)
