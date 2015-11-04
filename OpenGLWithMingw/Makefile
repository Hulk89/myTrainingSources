
all: build


build: test.cpp
	g++ -o test -Wall test.cpp -mwindows glut32.lib -lopengl32 -lglu32

clean:
	del test
