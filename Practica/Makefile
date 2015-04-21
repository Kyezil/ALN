all: main.out
	
main.out: main.cc Matrix.cc LU.cc
	g++ -std=c++11 Matrix.cc LU.cc main.cc -o main.out
clean:
	rm main.out
