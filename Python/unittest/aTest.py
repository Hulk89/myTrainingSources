from a import A

import unittest

class ATester(unittest.TestCase):
    def setUp(self):
        print "setUp called.."
        self.aa = A()

    def testGetA(self):
        print "testGetA.."
        self.assertEquals(self.aa.getA(), 'a')

    def testGetWrongA(self):
        print 'testGetWrongA..'
        self.assertEquals(self.aa.getWrongA(), 'a')

    def tearDown(self):
        print 'tearDown called..'

if __name__ == '__main__':
    testSuite = unittest.TestSuite()
    for testmethod in ('testGetA', 'testGetWrongA'):
        testSuite.addTest(ATester(testmethod))

    runner = unittest.TextTestRunner()
    runner.run(testSuite)
