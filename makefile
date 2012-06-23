NC=-I/usr/local/include
INC=
LIBS=

<<<<<<< HEAD
average_case: driver.o max.o permutations.o
	g++ $(INC) -o executables/average_case $(LIBS) ./executables/driver.o ./executables/max.o ./executables/permutations.o
driver.o: ./src/driver.cpp
	g++ $(LIB) $(INC) -c -o executables/driver.o ./src/driver.cpp
max.o: ./utils/math/max.cpp
	g++ $(LIB) $(INC) -c -o executables/max.o ./utils/math/max.cpp
permutations.o: ./utils/math/permutations.cpp
	g++ $(LIB) $(INC) -c -o executables/permutations.o ./utils/math/permutations.cpp
=======
average_case: driver.o polynomials.o
	g++ $(INC) -o executables/average_case $(LIBS) ./executables/driver.o ./executables/polynomials.o
driver.o: ./src/driver.cpp
	g++ $(LIB) $(INC) -c -o executables/driver.o ./src/driver.cpp
polynomials.o: ./utils/math/polynomials.cpp
	g++ $(LIB) $(INC) -c -o executables/polynomials.o ./utils/math/polynomials.cpp
>>>>>>> f38021cea418198c1ccd5d3507949a4b2a5ffc41
clean:
	rm executables/*.o ./executables/average_case

