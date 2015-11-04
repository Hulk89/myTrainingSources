.PHONY: all compile

OUT = ch01-04

LIBS += -ll

all: compile

compile: lex.yy.c
	gcc -o $(OUT) lex.yy.c  $(LIBS)
lex.yy.c: $(OUT).l
	lex $(OUT).l
clean:
	rm lex.yy.c
	rm $(OUT)
