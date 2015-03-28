CC=g++
CFLAGS=-c -Wall -O3
LDFLAGS=
SOURCES=LU.cc SQ_Matrix.cc test.cc
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm test.exe
