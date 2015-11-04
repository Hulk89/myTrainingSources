import ex1

sSentence = "All good things come to those who wait."

sWords = ex1.breakWords( sSentence )
print sWords
sSortedWords = ex1.sortWords( sWords )
print sSortedWords
ex1.printFirstWord( sWords )
ex1.printLastWord( sWords )
print sWords
ex1.printFirstWord( sSortedWords )
ex1.printLastWord( sSortedWords )
print sSortedWords

sSortedWords = ex1.sortSentence( sSentence )