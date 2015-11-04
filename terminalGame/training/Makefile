
.PHONY: all compile 01 02 03 04 05

all: compile

compile: 01 02 03 04 05
OUTS = 01_keyInput \
       02_moveAndDraw \
       03_boundaryAdded \
       04_clearScreen \
       05_thread

01: 01_keyInput
02: 02_moveAndDraw
03: 03_boundaryAdded
04: 04_clearScreen
05: 05_thread

clean:
	rm $(OUTS)

01_keyInput: 01_keyInput.c
	gcc -o $@ $<
02_moveAndDraw: 02_moveAndDraw.c
	gcc -o $@ $<
03_boundaryAdded: 03_boundaryAdded.c
	gcc -o $@ $<
04_clearScreen: 04_clearScreen.c
	gcc -o $@ $<
05_thread: 05_thread.c
	gcc -o $@ $<
