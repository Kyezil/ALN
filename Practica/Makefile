CXX=g++
CXX_FLAGS= -Wall -std=c++11
SRC=main.cc Matrix.cc LU_decomposition.cc
EXE=main.out

all: $(EXE)

fast: CXX_FLAGS += -O2
fast: $(EXE)
debug: CXX_FLAGS += -pg
debug: $(EXE)
generator: generator.cc
	$(CXX) $(CXX_FLAGS) generator.cc -o generator.out

$(EXE): $(SRC)
	$(CXX) $(CXX_FLAGS) $(SRC) -o $@

clean:
	rm $(EXE)
