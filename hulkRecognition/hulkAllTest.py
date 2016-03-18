
import unittest
from hulkSymbolTest import hulkSymbolTest
from hulkClassifierTest import hulkClassifierTest
from hulkAnalyzerTest import hulkAnalyzerTest

symbolTS = unittest.makeSuite( hulkSymbolTest, "test" )
classifierTS = unittest.makeSuite( hulkClassifierTest, "test" )
analyzerTS = unittest.makeSuite( hulkAnalyzerTest, "test" )
runner = unittest.TextTestRunner()
print "========================================================================"
print "hulkSymbolTest"
print "========================================================================"
runner.run(symbolTS)
print "========================================================================"
print "hulkClassifierTest"
print "========================================================================"
runner.run(classifierTS)
print "========================================================================"
print "hulkAnalyzerTest"
print "========================================================================"
runner.run(analyzerTS)



    
