from sys import argv

script, inputFile = argv

def print_all(f):
    print f.read()

def rewind(f):
    f.seek(0)

def print_a_line( line_count, f ):
    print line_count, f.readline(),

currentFile = open( inputFile )

print_all(currentFile)

rewind(currentFile)

for i in range( 1, 4 ):
    print_a_line(i, currentFile)

currentFile.close()
