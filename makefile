NC=-I/usr/local/include
INC=  -g
LIBS=  
CFLAGS = 
SHARE = 

average_case: driver.o polynomials.o permutations.o subtraction.o tuple.o
	mpic++ $(INC) -o executables/average_case ./executables/driver.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o $(LIBS)
parallel: parallel.o polynomials.o permutations.o subtraction.o tuple.o
	mpic++ $(INC) -o executables/parallel ./executables/parallel.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o $(LIBS)
test: polynomials.o permutations.o test.o subtraction.o tuple.o
	mpic++ $(INC) -o executables/test ./executables/test.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o $(LIBS)
tables: polynomials.o permutations.o tables.o subtraction.o tuple.o
	mpic++ $(INC) -o executables/tables ./executables/tables.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o $(LIBS)
parallel.o: ./src/parallel.cpp
	mpic++ $(INC) $(CFLAGS) -c -o executables/parallel.o ./src/parallel.cpp
driver.o: ./src/driver.cpp
	mpic++ $(INC) $(CFLAGS) -c -o executables/driver.o ./src/driver.cpp
polynomials.o: ./utils/math/polynomials.cpp
	mpic++ $(INC) $(CFLAGS) -c -o executables/polynomials.o ./utils/math/polynomials.cpp
permutations.o: ./utils/math/permutations.cpp
	mpic++ $(INC) $(CFLAGS) -c -o executables/permutations.o ./utils/math/permutations.cpp
subtraction.o: ./utils/math/subtraction.cpp
	mpic++ $(INC) $(CFLAGS) -c -o executables/subtraction.o ./utils/math/subtraction.cpp
test.o: ./test/test.cpp
	mpic++ $(INC) $(CFLAGS) -c -o executables/test.o ./test/test.cpp
tables.o: ./test/tables.cpp
	mpic++ $(LIBS) $(INC) $(CFLAGS) -c -o executables/tables.o ./test/tables.cpp
tuple.o: ./utils/math/tuple.cpp
	mpic++ $(INC) $(CFLAGS) -c -o executables/tuple.o ./utils/math/tuple.cpp
clean:
	rm executables/*

