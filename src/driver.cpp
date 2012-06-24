#include "../utils/basic/permutations.h"


int main()
{
    CoefTable C;
    GenTable G;
    std::cout << "Coefficients:";
    C.makeCoTable(20); // takes diameter
    C.makeMcoTable(20); //takes an arbitrary? bound
    std::cout << "\n Generators: \n";
    G.makeGenTable(30); //arbitrary? bound

    cout<<"Computing ...\n";

    for(int i; i<5; i++)
    {
            
    }

    return 0;

}
