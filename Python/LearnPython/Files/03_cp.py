# -*- coding: utf-8 -*-

from sys import argv
from os.path import exists

script , sFromFIle, sToFile = argv

sInFile = open(sFromFIle)
sInData = sInFile.read()

print "입력 파일크기 : %dbyte" % len(sInData)

print "출력파일 존재? %r" % exists( sToFile )

raw_input("OK : enter, NO : CTRL-C ")

sOutFile = open( sToFile, 'w' )
sOutFile.write( sInData )

print "Complete!!"

sOutFile.close()
sInFile.close()
