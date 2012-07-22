#include "../utils/basic/tuple.h"
#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "stdlib.h"
#include "string.h"
#include <bitset>
#include <time.h>
#include <iterator>

typedef std::vector<Polynomial> PolyVec;

using namespace std;


int makeTables(int diam, XCoTable *X, GenTable *A)
{
    clock_t start, end;
    start = clock();
    X->makeXCoTable(diam);
    cout <<"\nSize of X-Coefficient Table = " << X->size;
    A->makeGenTable(diam);
    cout <<"\nSize of Generator Table = " << A->size;
    end = clock();
    cout<<"\nTables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
    return X->size;
}


int main(int argc, char *argv[])
{
    if(argc<2)
    {
       cout<<"Usage: ./executables/average_case diameter (lowerbound) \n";
       return 0;
    }
	   XCoTable XTable;
       MCoTable QTable;
       GenTable ATable;
       const int diam = atoi(argv[1]);
	   int Xsize;
       const int d_cubed = diam*diam*diam; 
       const double lowerbound = (argv[2]) ? atoi(argv[2]) : (1); // should change!
       PolyVec best(diam*diam*diam*diam*diam); //holds the xcos table's size many polynomial: gives the history
       PolyVec temp(diam*diam*diam*diam*diam);
       vector<bool> cover;
       int counter = 0; //index for the bit array
       ifstream gens, xcoeffs, mcoeffs;
       ofstream out, archive;
       T6 A; //generators
       T6 Q; //m coefs
       T6 x; //x coefs
       Polynomial X;
       Polynomial M; //the bound itself
       Polynomial X_prime;
       Polynomial null;

       Polynomial mbest; //holds the highest valid m
       bool covered;
       clock_t start, end;
  
       start = clock();
       Xsize = makeTables(diam, &XTable, &ATable);
       gens.open("./permutationtables/GenTable.txt");
       if(gens){
       archive.open("./ms.txt");
	    while(gens >> A)
       {
		if(A[0] <= Xsize) //could really use a better upper bound here, as in the kfive case. Also, should add a similar check for k3, four
		{
		  QTable.makeMCoTable(diam, A[0], A[1], A[2], A[3], A[4]);
          mcoeffs.open("./permutationtables/MTable.txt");
          if(mcoeffs){
          while(mcoeffs >> Q)
          {

             M = Polynomial(A, Q);

           cover.clear();
           cover.resize(diam*diam*diam*diam);
             if((M.value() > mbest.value()) && M.wellFormed() && M.value() <= Xsize) //ignore M that are too big / small. like the above limit on the generators, there is room for improvement here
             {
                xcoeffs.open("./permutationtables/XTable.txt");
                if(xcoeffs){
                while(xcoeffs >> x)
                {
                   X = Polynomial(A, x);
                   X_prime = X-M;
                   if(X_prime.wellFormed())
					{ 
                   temp.at(X_prime.sum()) = X_prime;
                   cover[X_prime.sum()] = 1;
					}	
                }xcoeffs.close();
                // check covering
                covered = true;
                for(int i=0; i < M.sum(); ++i) //only check the first m of them
                {
                   if(cover[i]==0) //we are not covered
                   {
                     covered = false;
                     break;
                   }
                }
                if(covered)
                {
                   mbest=M;
                   for(int j =0; j < mbest.sum(); ++j)
                      {
                         best[j] = temp[j];
                      }
                   archive << mbest << mbest.A << endl;
                }
            }}
          }}mcoeffs.close();
       }}}gens.close();
   end = clock();
//need to write out mbest and best to a file.	
   out.open("./results.txt");
   if(out)
      {
         out << "d: " << diam << endl;
         out << "modulus: " << mbest << endl;
         out << "generators: " << best[0].A << endl;
         for(int i=0; i < mbest.sum(); ++i)
         {
            out << best[i];
            out << best[i].s;
         }
         out<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n \n";
      }
   out.close();
   archive.close();
   cout<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n \n";
 
   return 0;

}
