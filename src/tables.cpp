#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#define diamCubed 1000
#define xSize 286
using namespace std;


int main()
{
    CoefTable C;
    GenTable G;
    //std::cout << "Coefficients:";
    C.makeCoTable(10); // takes diameter
    C.makeMcoTable(10); //takes an arbitrary? bound
    //std::cout << "\n Generators: \n";
    G.makeGenTable(10); //arbitrary? bound
    std::cout <<"\n cotSize:" << C.getCotSize() << "\n mtSize:" << C.getMtSize() << "\n gSize:" << G.getGsize() << endl;
    return 0;
}


