def fib2(n):  # write Fibonacci series up to n
    """Return a Fibonacci series up to n."""
    sResult = []; # it can be result = result + [a] but more efficient
    a, b = 0, 1
    while a < n:
        sResult.append(a);
        a, b = b, a+b
    return sResult

fib100 = fib2(100)
print( fib100 )
