
.PHONY: all compile 

all: compile

OUT = tetris


SRCS =  htDraw.c\
        htBlock.c\
        htKey.c\
        htUpdate.c\
        htMain.c
OBJS = $(SRCS:.c=.o)

.c.o:
	gcc -c -o $@ $<

clean:
	rm $(OBJS)
	rm $(OUTS)

compile: $(OBJS)
	gcc -o $(OUT) $(OBJS)
