NC=-I/usr/local/include
INC=  -g
LIBS=  
CFLAGS = 
SHARE = 

average_case: driver.o polynomials.o permutations.o subtraction.o
	g++ $(INC) -o executables/average_case $(LIBS) ./executables/driver.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
analysis: analysis.o polynomials.o permutations.o subtraction.o
	g++ $(INC) -o executables/analysis $(LIBS) ./executables/analysis.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
test: polynomials.o permutations.o test.o subtraction.o
	g++ $(INC) -o executables/test $(LIBS) ./executables/test.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
tables: polynomials.o permutations.o tables.o subtraction.o
	g++ $(INC) -o executables/tables $(LIBS) ./executables/tables.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
analysis.o: ./src/analysis.cpp
	g++ $(LIB) $(INC) -c -o executables/analysis.o ./src/analysis.cpp
driver.o: ./src/driver.cpp
	g++ $(INC) $(CFLAGS) -c -o executables/driver.o ./src/driver.cpp
polynomials.o: ./utils/math/polynomials.cpp
	g++ $(INC) $(CFLAGS) -c -o executables/polynomials.o ./utils/math/polynomials.cpp
permutations.o: ./utils/math/permutations.cpp
	g++ $(INC) $(CFLAGS) -c -o executables/permutations.o ./utils/math/permutations.cpp
subtraction.o: ./utils/math/subtraction.cpp
	g++ $(INC) $(CFLAGS) -c -o executables/subtraction.o ./utils/math/subtraction.cpp
test.o: ./test/test.cpp
	g++ $(LIB) $(INC) -c -o executables/test.o ./test/test.cpp
tables.o: ./test/tables.cpp
	g++ $(LIB) $(INC) -c -o executables/tables.o ./test/tables.cpp
clean:
	rm executables/*
