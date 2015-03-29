CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCES=practica1.cc
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm main.exe matrius_LU.dat inversa_A.dat
