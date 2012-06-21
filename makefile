NC=-I/usr/local/include
INC=
LIBS=

average_case: driver.o
	g++ $(INC) -o executables/average_case $(LIBS) driver.o
driver.o: ./driver.cpp
	g++ $(LIB) $(INC) -c -o executables/driver.o ./driver.cpp
clean:
	rm executables/*.o ./executables/average_case

