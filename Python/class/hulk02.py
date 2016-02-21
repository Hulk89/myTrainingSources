from hulk01 import hulk01

class hulk02( object ):
    def __init__( self, aList = [] ):
        self.mCount = len( aList )
        self.mList = sorted( aList )
    def __repr__( self ):
        reprStr = "Total Number : " + str( self.mCount ) + ", List : [";

        for item in self.mList:
            if item != self.mList[ len( self.mList ) - 1] :
                reprStr += str( item ) + ", "
            else:
                reprStr += str( item )
        reprStr = reprStr + " ] "
        return  reprStr
# http://blog.leekchan.com/post/19062594439/python에서-효율적인-string-concatenation-방법
'''
Method 4: Build a list of strings, then join it

def method4():
    str_list = []
    for num in xrange(loop_count):
        str_list.append(`num`)
    return ''.join(str_list)

이 방법은 일반적으로 추천되는 pythonic way라고 소개하고 있다. 
Concatenation할 요소들을 list에 담은다음 join으로 합쳐서 문자열을 생성하는 방법이다.
'''

if __name__ == "__main__":
    
    hulkList = [ hulk01( "first", 1 ),
                 hulk01( "john", 23 ),
                 hulk01( "bill", 40 ),
                 hulk01( "favorite", 36 ),
                 hulk01( "hate", 26 ) ]
    hulkClass = hulk02( hulkList )

    print hulkClass
