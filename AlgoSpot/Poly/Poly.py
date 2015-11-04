
def case( n, m ):
    result = n + m - 1
    return result

def poly( n, firstBlock ):
    if n == firstBlock:
        return 1
    else:
        sum = 0
        for dd in range( 1, n - firstBlock + 1 ):
            tmp = poly( n - firstBlock, dd )
            sum = sum + ( tmp * case( dd, firstBlock ) );
        return sum



def poly2( n ):
    sum = 0
    for myBlock in range( 1, n ):
        m = n - myBlock
        for firstBlock in range( 1, m + 1 ):
            tmp = poly( m, firstBlock )
            sum = sum + ( tmp * case ( myBlock, firstBlock ) );
    sum = sum + 1;
    return sum

print( poly2(2) )
print( poly2(4) )
print( poly2(3) )
