NC=-I/usr/local/include
INC= -g
LIBS=

average_case: driver.o polynomials.o permutations.o subtraction.o
	mpic++ $(INC) -o executables/average_case $(LIBS) ./executables/driver.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
parallel: parallel.o polynomials.o permutations.o subtraction.o
	mpic++ $(INC) -o executables/parallel $(LIBS)  ./executables/parallel.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
test: polynomials.o permutations.o test.o subtraction.o
	mpic++ $(INC) -o executables/test $(LIBS) ./executables/test.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
tables: polynomials.o permutations.o tables.o subtraction.o
	g++ $(INC) -o executables/tables $(LIBS) ./executables/tables.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
parallel.o: ./src/parallel.cpp
	mpic++ $(LIBS) $(INC) -c -o executables/parallel.o ./src/parallel.cpp
driver.o: ./src/driver.cpp
	g++ $(LIBS) $(INC) -c -o executables/driver.o ./src/driver.cpp
polynomials.o: ./utils/math/polynomials.cpp
	g++ $(LIBS) $(INC) -c -o executables/polynomials.o ./utils/math/polynomials.cpp
permutations.o: ./utils/math/permutations.cpp
	g++ $(LIBS) $(INC) -c -o executables/permutations.o ./utils/math/permutations.cpp
subtraction.o: ./utils/math/subtraction.cpp
	g++ $(LIBS) $(INC) -c -o executables/subtraction.o ./utils/math/subtraction.cpp
test.o: ./test/test.cpp
	mpic++ $(INC) $(LIBS) -c -o executables/test.o ./test/test.cpp
tables.o: ./test/tables.cpp
	g++ $(LIBS) $(INC) -c -o executables/tables.o ./test/tables.cpp
clean:
	rm executables/*

