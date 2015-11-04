
words = ['aaa', 'bbb', 'ccc']

for w in words[:]:
    if w == 'aaa' or w == 'bbb':
        words.insert(len(words),w)
print words
