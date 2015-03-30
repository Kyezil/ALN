CXX=g++
CXXFLAGS=-c -Wall -Wextra -pedantic-errors -std=c++11
SRC=practica1.cc
OBJ=$(SRC:.cc=.o)
EXECUTABLE=main.exe

all: $(SRC) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJ)
	$(CXX) $(OBJ) -o $@

.cc.o:
	$(CXX) $(CXXFLAGS) $< -o $@
clean:
	rm main.exe matrius_LU.dat inversa_A.dat sol_Axb.dat
