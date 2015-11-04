# -*- coding: utf-8 -*-

# close - 파일 닫기
# read 
# readline
# truncate
# write

from sys import argv

script, fileName = argv

txt = open( fileName )

print "파일 %r의 내용:" % fileName
print txt.read()
txt.close()

print "파일 이름을 다시 입력해 주세요."
file_again = raw_input(">")

txt_again = open(file_again)

print txt_again.read()
txt_again.close()
