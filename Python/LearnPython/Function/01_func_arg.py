
def print2(*args):
    arg1, arg2 = args
    print "arg1: %r, arg2: %r" % ( arg1, arg2 )

def print2Again(arg1,arg2):
    print "arg1: %r, arg2: %r" % ( arg1, arg2 )

def print1( arg1 ):
    print "arg1: %r" % arg1

def print_none():
    print "No"

print2("zed", "shaw")
print2Again("zed","shaw")
print1("First!")
print_none()

