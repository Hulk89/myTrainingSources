# -*- coding: utf-8 -*-

from sys import argv
prompt = 'Siri>'

script, userName = argv

print "Hello %s. I'am %s script." % ( userName, script )
print "I have a few question."
print "%s, Do you like me?" % userName
likes = raw_input(prompt)

print "Where do you live in?"
lives = raw_input(prompt)

print """
Well, you answered '%s' when I asked you weather you like me.
You lived in  '%s' I don't know where is '%s'.
""" % ( likes, lives, lives )


