#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include "time.h"

using namespace std;


int main(int argc, char *argv[])
{
    clock_t start, end;
    if(argc<4){
       std::cout<< "Usage: ./executables/tables int int int \n";
       return 0;
    }
    else{
       start = clock();
       CoefTable C;
       GenTable G;
       //std::cout << "Coefficients:";
       C.makeCoTable(atoi(argv[1])); // takes diameter
       C.makeMcoTable(atoi(argv[2])); //takes an arbitrary? bound
       //std::cout << "\n Generators: \n";
       G.makeGenTable(atoi(argv[3])); //arbitrary? bound
       end = clock();
       std::cout<<"Tables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
       std::cout <<"\n cotSize:" << C.getCotSize() << "\n mtSize:" << C.getMtSize() << "\n gSize:" << G.getGsize() << endl;
       
       return 0;
    }
}


