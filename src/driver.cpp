#include "../utils/basic/tuple.h"
#include "../utils/basic/permutations.h"
#include "../utils/basic/polynomials.h"
#include "../utils/basic/subtraction.h"
#include "string.h"
#include <bitset>
#include "boost/dynamic_bitset.hpp"
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
    return 0;
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
       const int d_cubed = diam*diam*diam; 
       const double lowerbound = (argv[2]) ? atoi(argv[2]) : (1); // should change!
       PolyVec best(diam*diam*diam*diam*diam); //holds the xcos table's size many polynomial: gives the history
       PolyVec temp(diam*diam*diam*diam*diam);
       boost::dynamic_bitset<> cover(diam*diam*diam*diam*diam); 
       int counter = 0; //index for the bit array
       ifstream gens, xcoeffs, mcoeffs;
       ofstream out, archive;
       T5 A; //generators
       T5 Q; //m coefs
       T5 x; //x coefs
       Polynomial X;
       Polynomial M; //the bound itself
       Polynomial X_prime;
       Polynomial null;
       Polynomial mbest; //holds the highest valid m
       bool covered;
       clock_t start, end;
       start = clock();
       makeTables(diam, &XTable, &ATable);
       gens.open("./permutationtables/GenTable.txt");
       if(gens){
       archive.open("./ms.txt");
	    while(gens >> A)
       {
		//cout << "A: " << A << endl;
		  QTable.makeMCoTable(diam, A[0], A[1], A[2], A[3]);
          mcoeffs.open("./permutationtables/MTable.txt");
          if(mcoeffs){
          while(mcoeffs >> Q)
          {
			//cout << "in mco loop" << endl;
			//cout << Polynomial(T5(0,3,6,9,12),T5(1,2,3,4,5));
			//cout << "assigned a poly" << endl;
             M = Polynomial(A, Q);

			//cout << "made an M" << endl;
			//cout << M << endl;
             cover.reset();
             if(!M.wellFormed()){cout << "NOT WELL FORMED!" << endl;}
             if((M.value() > mbest.value()) && M.wellFormed() ) //ignore M that are too small, or badly formed
             {
                xcoeffs.open("./permutationtables/XTable.txt");
                if(xcoeffs){
                while(xcoeffs >> x)
                {
					//cout << "in xco loop" << endl;
                   X = Polynomial(A, x);
					//cout << "subtracting... ";
                   X_prime = X-M;
					//cout << " subtraction worked" << endl;
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
                     //cout << "uncovered: " << i << endl;
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
       }}gens.close();
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
