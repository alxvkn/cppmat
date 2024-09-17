CXX = clang++

CXXFLAGS=-std=c++23 -Wall -Wconversion

test: test.o Matrix.hpp
	$(CXX) $< -o $@

test_dynamic: test_dynamic.o DynamicMatrix.hpp
	$(CXX) $< -o $@

run: test
	./test

clean:
	rm *.o test test_dynamic

.PHONY: clean run
