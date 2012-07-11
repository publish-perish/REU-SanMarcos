#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include "time.h"

using namespace std;


int main(int argc, char *argv[])
{
    clock_t start, end;
    if(argc<2){
       std::cout<< "Usage: ./executables/tables diameter \n";
       return 0;
    }
    else{
       start = clock();
       XCoTable XTable;
       GenTable GenTable;
       //std::cout << "Coefficients:";
       XTable.makeXCoTable(atoi(argv[1]));
      // C.makeMcoTable(atoi(argv[1]));
       //std::cout << "\n Generators: \n";
       GenTable.makeGenTable(atoi(argv[1]));
       end = clock();
       std::cout<<"Tables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
       std::cout <<"\nSize of X-Coeff Table:" << XTable.size << "\nSize of Generator Table:" << GenTable.size  << endl;
       
       return 0;
    }
}

