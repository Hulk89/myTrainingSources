import tokenize

string = input( "Please enter the string:" )

print( '입력한 글 : ' + string )
tokens = string.split();
idx = 0

for token in tokens:
    idx = idx + 1

    token = token.replace('가','')
    token = token.replace('은','')
    token = token.replace('는','')
    token = token.replace('이','')


    string2 = str(idx) + '번째 어절 : ' + token
    print( string2 )
  


