
CC = g++
CXXFLAGS = -std=c++11

test: test.cpp maze.o mouse.o 
	$(CC) $(CXXFLAGS) $^ -o $@
	@./test

mouse.o: mouse.cpp mouse.hpp

maze.o: maze.cpp maze.hpp Node.hpp

test2: test2.cpp

clean:
	rm test a.out mouse.o maze.o





