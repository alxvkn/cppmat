CXX = clang++

CXXFLAGS=-std=c++23 -Wall -Wconversion

mat: mat.o
	$(CXX) $^ -o $@

run: mat
	./mat

clean:
	rm mat.o mat
