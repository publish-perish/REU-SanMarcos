NC=-I/usr/local/include
INC=
LIBS=

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

clean:
	rm executables/*

