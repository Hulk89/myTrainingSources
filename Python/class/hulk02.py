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
# http://blog.leekchan.com/post/19062594439/python����-ȿ������-string-concatenation-���
'''
Method 4: Build a list of strings, then join it

def method4():
    str_list = []
    for num in xrange(loop_count):
        str_list.append(`num`)
    return ''.join(str_list)

�� ����� �Ϲ������� ��õ�Ǵ� pythonic way��� �Ұ��ϰ� �ִ�. 
Concatenation�� ��ҵ��� list�� �������� join���� ���ļ� ���ڿ��� �����ϴ� ����̴�.
'''

if __name__ == "__main__":
    
    hulkList = [ hulk01( "first", 1 ),
                 hulk01( "john", 23 ),
                 hulk01( "bill", 40 ),
                 hulk01( "favorite", 36 ),
                 hulk01( "hate", 26 ) ]
    hulkClass = hulk02( hulkList )

    print hulkClass
