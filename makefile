NC=-I/usr/local/include
INC= -g
LIBS=

test: test.o polynomials.o permutations.o tuple.o
	g++ $(INC) -o executables/test $(LIBS) ./executables/test.o ./executables/polynomials.o ./executables/permutations.o ./executables/tuple.o
average_case: driver.o polynomials.o permutations.o tuple.o
	g++ $(INC) -o executables/average_case $(LIBS) ./executables/driver.o ./executables/polynomials.o ./executables/permutations.o ./executables/tuple.o
driver.o: ./src/driver.cpp
	g++ $(LIB) $(INC) -c -o executables/driver.o ./src/driver.cpp
polynomials.o: ./utils/math/polynomials.cpp
	g++ $(LIB) $(INC) -c -o executables/polynomials.o ./utils/math/polynomials.cpp
permutations.o: ./utils/math/permutations.cpp
	g++ $(LIB) $(INC) -c -o executables/permutations.o ./utils/math/permutations.cpp
tuple.o: ./utils/math/tuple.cpp
	g++ $(LIB) $(INC) -c -o executables/tuple.o ./utils/math/tuple.cpp
test.o: ./src/test.cpp
	g++ $(LIB) $(INC) -c -o executables/test.o ./src/test.cpp

clean:
	rm executables/*

