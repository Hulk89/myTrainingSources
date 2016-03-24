
import unittest
import cv2

from hulkClassifier import hulkClassifier
import hulkSegInfo 
class hulkClassifierTest( unittest.TestCase ):
    
    def setUp(self):
    	self.mHulkClassifier = hulkClassifier()
    	self.mImg = cv2.imread('Images/lessTest.png', 0)
    
    
    def testClassify( self ):
		sClassNum = self.mHulkClassifier.Classification(self.mImg)
		
		self.assertEqual( hulkSegInfo.getSegInfo(sClassNum).mChar, "<" )

		self.assertTrue( self.mHulkClassifier.getMinDistance(self.mImg, sClassNum) < 4.3 )

		self.assertTrue ( self.mHulkClassifier.isRatioReasonable(self.mImg, sClassNum) )


if __name__ == '__main__':
    TS = unittest.makeSuite( hulkClassifierTest,"test")
    runner = unittest.TextTestRunner()
    runner.run(TS)



    
