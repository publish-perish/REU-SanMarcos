NC=-I/usr/local/include
INC= -g
LIBS=

average_case: driver.o polynomials.o permutations.o subtraction.o
	g++ $(INC) -o executables/average_case $(LIBS) ./executables/driver.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
test: polynomials.o permutations.o test.o subtraction.o
	g++ $(INC) -o executables/test $(LIBS) ./executables/test.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
driver.o: ./src/driver.cpp
	g++ $(LIB) $(INC) -c -o executables/driver.o ./src/driver.cpp
polynomials.o: ./utils/math/polynomials.cpp
	g++ $(LIB) $(INC) -c -o executables/polynomials.o ./utils/math/polynomials.cpp
permutations.o: ./utils/math/permutations.cpp
	g++ $(LIB) $(INC) -c -o executables/permutations.o ./utils/math/permutations.cpp
subtraction.o: ./utils/math/subtraction.cpp
	g++ $(LIB) $(INC) -c -o executables/subtraction.o ./utils/math/subtraction.cpp
test.o: ./test/test.cpp
	g++ $(LIB) $(INC) -c -o executables/test.o ./test/test.cpp
clean:
	rm executables/*

