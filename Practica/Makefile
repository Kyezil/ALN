CXX=g++
CXX_FLAGS= -Wall -std=c++11
SRC=main.cc Matrix.cc LU.cc
EXE=main.out

all: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(CXX_FLAGS) $(SRC) -o $@

clean:
	rm $(EXE)
