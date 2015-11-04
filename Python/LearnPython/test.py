# -*- coding: utf-8 -*-

from sys import exit

def goldRoom():
    print "This is the room of gold. How much you take?"

    next = raw_input(">")

    if "0" in next or "1" in next:
        howMuch = int(next)
    else:
        dead("You must know writing numbers!")

    if howMuch < 50:
        print "You win!"
        exit(0)
    else:
        dead("Fuck you")
def dead(why):
    print why, "Bye"
    exit(0)
goldRoom()


