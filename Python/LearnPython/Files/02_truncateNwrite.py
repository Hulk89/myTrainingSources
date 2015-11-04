# -*- coding: utf-8 -*-

# close - 파일 닫기
# read 
# readline
# truncate
# write

from sys import argv

script, fileName = argv

print "%r 파일을 지우려 합니다." % fileName
print "취소하려면 CTRL-C(^C)를 누르세요."
print "진행하려면 리턴을 누르세요."

raw_input("?")

print "파일 여는 중..."

target = open( fileName, 'w' )

print "파일 내용을 지웁니다."
target.truncate()

print "새로 파일 쓰기"

line = []
for i in [0,1,2]:
    print i
    sStr = str(i+1) + "줄: "
    txt = raw_input(sStr)
    line.append(txt)
print line
print "이 내용을 파일에 씁니다."
for i in [0,1,2]:
    target.write(line[i])
    target.write("\n")

print "마지막으로 닫습니다."
target.close()

