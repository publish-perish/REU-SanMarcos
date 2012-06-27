#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"

using namespace std;


int main(int argc, char *argv[])
{
    if(argc<4){
       std::cout<< "Usage: ./executables/tables int int int \n";
       return 0;
    }
    else{
       CoefTable C;
       GenTable G;
       //std::cout << "Coefficients:";
       C.makeCoTable(atoi(argv[1])); // takes diameter
       C.makeMcoTable(atoi(argv[2])); //takes an arbitrary? bound
       //std::cout << "\n Generators: \n";
       G.makeGenTable(atoi(argv[3])); //arbitrary? bound
       std::cout <<"\n cotSize:" << C.getCotSize() << "\n mtSize:" << C.getMtSize() << "\n gSize:" << G.getGsize() << endl;
       return 0;
    }
}


