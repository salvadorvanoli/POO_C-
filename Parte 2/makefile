all: A.o B.o C.o main.o
	g++ A.o B.o C.o main.o -o programa.exe

main.o: main.cpp A.h B.h C.h
	g++ -c main.cpp -o main.o

A.o: A.cpp A.h
	g++ -c A.cpp -o A.o

B.o: B.cpp B.h A.h
	g++ -c B.cpp -o B.o

C.o: C.cpp C.h B.h
	g++ -c C.cpp -o C.o

clean:
	del /Q main.o A.o B.o C.o programa.exe

run:
	make clean
	make
	cls
	programa.exe