CXX=g++
CXX_FLAGS= -Wall -std=c++11
SRC=main.cc Matrix.cc LU.cc
EXE=main.out

all: $(EXE)

fast: CXX_FLAGS += -Ofast
fast: $(EXE)
debug: CXX_FLAGS += -g
debug: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(CXX_FLAGS) $(SRC) -o $@

clean:
	rm $(EXE)
