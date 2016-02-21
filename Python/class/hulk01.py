#-*- coding: utf-8 -*-

class hulk01(object):

    def __init__( self, aName = "", aAge = 0 ):
        self.mName = aName
        self.mAge  = aAge

    def __repr__( self ):
        return "Name : " + self.mName + ", Age : " + str( self.mAge )

    def __str__( self ):
        return "Name : " + self.mName + ", Age : " + str( self.mAge )

    def __cmp__( self, aOther ):
        if self.mAge < aOther.mAge :
            return -1
        elif self.mAge > aOther.mAge :
            return 1
        else:
            return 0

if __name__ == "__main__":

    print "One instance representation test"

    hulk = hulk01( "HULK", 28 )
    print hulk

    print "Compare Test"

    hulkList = [ hulk01( "Hulk28", 28 ),
                 hulk01( "Hulk19", 19 ),
                 hulk01( "Hulk14", 14 ),
                 hulk01( "Hulk23", 23 ),
                 hulk01( "Hulk7", 7 ),
                 hulk01( "Hulk1", 1 ) ];
    
    print hulkList

    hulkList.sort()
    print hulkList

    hulkListSorted = sorted( hulkList )
    print hulkListSorted
