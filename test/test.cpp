#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;


int main(int argc, char *argv[])
{
    clock_t start, end;
    if(argc<5){
       std::cout<< "Usage: ./executables/tables diameter numprocs b c1\n";
       return 0;
    }
    else{
       start = clock();
       XCoTable XTable;
       GenTable GenTable;
       MCoTable MTable;
       //std::cout << "Coefficients:";
        XTable.makeXCoTable(atoi(argv[1]), atoi(argv[2]));
       //MTable.makeMCoTable(atoi(argv[1]), atoi(argv[3]), atoi(argv[4]), atoi(argv[2]));
       //std::cout << "\n Generators: \n";
       GenTable.makeGenTable(atoi(argv[1]));
       end = clock();
       std::cout<<"Tables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
       std::cout <<"\nSize of X-Coeff Table:" << XTable.size << "\nSize of Generator Table:" << GenTable.size<<endl;;
       //std::cout<<"\nTesting M-Coeff Table, size is :"<<MTable.size<<endl;

       ifstream gens;

       T A, B;
       B = T(1, 2, 4);
       A = T(3, 5, 4);
cout<<"A "<<A<<" B "<<B<<endl;
       A = B;
       cout<<"B "<<B<<endl;
       B = T(3, 3, 3);
       cout<<"B "<<B<<endl;
       Polynomial P;

       Polynomial p(B, A);

cout<<p;

       cout<<P;
       P.A = A;

cout<<P;
P.Y = p.Y;
cout<<P;

       
       /*
       cout<<B<<endl;
       gens.open("./permutationtables/GenTable.txt");
       if(gens){
           while(!gens.eof()){
           gens >> A >> B;

       Polynomial P(A, B);
cout<< P;}}*/
       return 0;
    }

    }


