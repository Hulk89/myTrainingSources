# -*- coding: utf-8 -*-

def breakWords( aStuff ):
    """이 함수는 문자열을 단어로 쪼개 줍니다."""
    sWords = aStuff.split(' ')
    return sWords

def sortWords( aWords ):
    """단어 정렬!!"""
    return sorted( aWords ) # 이거는 원래 있는 함수인가보네??

def printFirstWord( aWords ):
    """첫 단어를 꺼내 출력!"""
    sWord = aWords.pop(0)
    print sWord

def printLastWord( aWords ):
    """마지막 단어 출력!"""
    sWord = aWords.pop(-1)
    print sWord

def sortSentence( aSentence ):
    """한 문장을 통째로 받아 단어를 정렬시켜 반환!"""
    sWords = breakWords( aSentence )
    return sortWords(sWords)

def printFirstNLast( aSentence ):
    """문장의 처음과 끝 단어 출력"""
    sWords = breakWords( aSentence )
    printFirstWord( sWords )
    printLastWord( sWords )

def printFirstNLastSorted( aSentence ):
    """단어 정렬 -> 처음, 마지막 단어 출력!"""
    sWords = sortSentence( aSentence )
    printFirstWord( sWords )
    printLastWord( sWords )

