all: test.exe

test.exe: LU.o test.o
	g++ LU.o test.o -o test.exe
LU.o: LU.cc
	g++ -c LU.cc
test.o: test.cc
	g++ -c test.cc

clean:
	rm *.o test.exe
