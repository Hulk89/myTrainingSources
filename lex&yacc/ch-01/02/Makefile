.PHONY: all compile

OUT = ch01-02

LIBS += -ll

all: compile

compile: lex.yy.c
	gcc -o $(OUT) lex.yy.c  $(LIBS)
lex.yy.c: ch01-02.l
	lex ch01-02.l
clean:
	rm lex.yy.c
	rm $(OUT)
