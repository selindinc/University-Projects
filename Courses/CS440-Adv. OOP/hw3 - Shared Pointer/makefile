FLAGS = -std=c++14 -Wall -Wextra -pedantic -g -pthread -Wno-sized-deallocation -O

all: smart_ptr

.PHONY: smart_ptr

smart_ptr: SharedPtr_test.cpp SharedPtr.hpp
	g++ SharedPtr_test.cpp -o shared_ptr_test $(FLAGS)

clean:
	rm -rf *.dSYM *.o shared_ptr_test

