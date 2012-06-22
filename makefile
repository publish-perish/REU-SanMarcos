NC=-I/usr/local/include
INC=
LIBS=

average_case: driver.o max.o permutations.o
	g++ $(INC) -o executables/average_case $(LIBS) ./executables/driver.o ./executables/max.o ./executables/permutations.o
driver.o: ./src/driver.cpp
	g++ $(LIB) $(INC) -c -o executables/driver.o ./src/driver.cpp
max.o: ./utils/math/max.cpp
	g++ $(LIB) $(INC) -c -o executables/max.o ./utils/math/max.cpp
permutations.o: ./utils/math/permutations.cpp
	g++ $(LIB) $(INC) -c -o executables/permutations.o ./utils/math/permutations.cpp
clean:
	rm executables/*.o ./executables/average_case

