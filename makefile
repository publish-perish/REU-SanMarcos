NC=-I/usr/local/include
INC= -g
LIBS=

average_case: driver.o permutations.o
	g++ $(INC) -o executables/average_case $(LIBS) ./executables/driver.o ./executables/permutations.o 
tables: polynomials.o permutations.o tables.o subtraction.o
	g++ $(INC) -o executables/tables $(LIBS) ./executables/tables.o ./executables/polynomials.o ./executables/permutations.o ./executables/subtraction.o
analysis.o: ./src/analysis.cpp
	g++ $(LIB) $(INC) -c -o executables/analysis.o ./src/analysis.cpp
driver.o: ./src/driver.cpp
	g++ $(LIB) $(INC) -c -o executables/driver.o ./src/driver.cpp
permutations.o: ./utils/math/permutations.cpp
	g++ $(LIB) $(INC) -c -o executables/permutations.o ./utils/math/permutations.cpp
test.o: ./test/test.cpp
	g++ $(LIB) $(INC) -c -o executables/test.o ./test/test.cpp
tables.o: ./test/tables.cpp
	g++ $(LIB) $(INC) -c -o executables/tables.o ./test/tables.cpp
clean:
	rm executables/*
