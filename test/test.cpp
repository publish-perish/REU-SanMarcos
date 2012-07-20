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

       T A, B, C, Z;
       B = T(1, 2, 4);
       A = T(10, 5, 1);
       C = T(1, 1, 1);

       cout<< "A : "<<A<<" B : "<<B<<endl;
      // C = A - B;

       //cout<< C<<endl;
       cout<<"A>B :"<< (A>B)<<endl;


       Polynomial P1(C, A);
       Polynomial P2(C, B);

       cout<<"P1 "<<P1;
       cout<<"P2 "<<P2;
       
       Polynomial P3 = (P1-P2);

       cout<<"P1.Y > P2.Y :"<< (P1.Y > P2.Y)<<endl;
       cout<<"P3 = P1 - P2  :\n";
       cout <<P3;
       
       
       Polynomial P4(A, C);
       Polynomial P5(P4 - P2);

       cout<<"P5 = P4 - P2  :"<<P5;

       P5 = P4;
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


