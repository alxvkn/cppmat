CXX = clang++

CXXFLAGS=-std=c++23 -Wall -Wconversion

test: test.o
	$(CXX) $^ -o $@

run: test
	./test

clean:
	rm test.o test
