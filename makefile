NC=-I/usr/local/include
INC=
LIBS=

average_case: driver.o polynomials.o
	g++ $(INC) -o executables/average_case $(LIBS) ./executables/driver.o ./executables/polynomials.o
driver.o: ./src/driver.cpp
	g++ $(LIB) $(INC) -c -o executables/driver.o ./src/driver.cpp
polynomials.o: ./utils/math/polynomials.cpp
	g++ $(LIB) $(INC) -c -o executables/polynomials.o ./utils/math/polynomials.cpp
clean:
	rm executables/*.o ./executables/average_case

