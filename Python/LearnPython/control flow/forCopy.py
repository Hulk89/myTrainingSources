words = [ 'cat', 'window', 'defenestrate' ]
for w in words[:]: # copy of List
    if len(w) > 6:
        words.insert( 0, w )
print( words );
