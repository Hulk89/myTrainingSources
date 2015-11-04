
llTest : main.o ll.o
	gcc -lm -g -o llTest main.o ll.o

ll.o : ll.c ll.h
	gcc -c -g ll.c

main.o : main.c ll.h
	gcc -c -g main.c


clean :
	rm ll.o llTest main.o LinkedList.tar

dist :
	tar cvf LinkedList.tar *
