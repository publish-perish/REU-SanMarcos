NC=-I/usr/local/include
INC= -static 
LIBS= -lpolynomials -ltuple -lpermutations -lsubtraction -L/home/repos/REU-SanMarcos/executables 
CFLAGS = -fpic
SHARE = -shared

average_case: driver.o polynomials.o permutations.o subtraction.o tuple.o
	mpic++ $(INC) -o executables/average_case ./executables/driver.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o $(LIBS)
parallel: parallel.o polynomials.o permutations.o subtraction.o tuple.o
	mpic++ $(INC) -o executables/parallel ./executables/parallel.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o $(LIBS)
test: polynomials.o permutations.o test.o subtraction.o tuple.o
	mpic++ $(INC) -o executables/test ./executables/test.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o $(LIBS)
tables: polynomials.o permutations.o tables.o subtraction.o tuple.o
	mpic++ $(INC) -o executables/tables ./executables/tables.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o $(LIBS)
polynomials.so:
	mpic++ $(SHARE) -o executables/libpolynomials.so ./executables/polynomials.o
permutations.so:
	mpic++ $(SHARE) -o executables/libpermutations.so ./executables/permutations.o
subtraction.so:
	mpic++ $(SHARE) -o executables/libsubtraction.so ./executables/subtraction.o
tuple.so:
	mpic++ $(SHARE) -o executables/libtuple.so ./executables/tuple.o
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

