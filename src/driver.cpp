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
    /*cout << "X Coeffs \n";
    for(std::vector<T>::iterator x = X->XCoeffs.begin(); x != X->XCoeffs.end(); ++x)
    {
      cout << *x << " ";
    }
    cout <<"\nSize of X-Coefficient Table = " << X->XTableSize() << endl << endl;
    */
    A->makeGenTable(diam);
    /*cout << "Generators \n";
	 for(std::vector<T>::iterator a = A->Generators.begin(); a != A->Generators.end(); ++a)
    {
      cout << *a <<" ";
    }
    cout <<"\nSize of Generator Table = " << A->GenTableSize() << endl;
    */
    end = clock();
    //cout<<"Tables were generated in "<<(double)(end - start)/(double)CLOCKS_PER_SEC<<" seconds.\n";
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
       const double lowerbound = (argv[2]) ? atoi(argv[2]) : (d_cubed/16.0);
       PolyVec best(d_cubed); //holds the xcos table's size many polynomial: gives the history
       PolyVec temp(d_cubed);
       boost::dynamic_bitset<> cover(d_cubed); // diam cubed: larger than needed, but hard to make sharp
       bool covered =false;
       int counter = 0; //index for the bit array
       ifstream gens; // c, b, a
       ifstream mcos; // gamma, beta, alpha
       ifstream xcos; // x3, x2, x1
       ofstream out; //output
       ofstream archive;
       T A; //generators
       T Q; //m coefs
       T x; //x coefs
       Polynomial X;
       Polynomial M; //the bound itself
       Polynomial X_prime;
       Polynomial null;
       Polynomial mbest = Polynomial(T(0,0,0), T(0,0,0)); //holds the highest valid m
       
       clock_t start, end;

    
       start = clock();
       makeTables(diam, &XTable, &ATable);
       archive.open("./ms.txt");
	    for(std::vector<T>::iterator a = ATable.Generators.begin(); a != ATable.Generators.end(); ++a)
       {
		    //cout << *A << endl;
          double c1 = get<0>(*a)/get<1>(*a);
		    QTable.makeMCoTable(diam, get<1>(*a), c1);
			 for(std::vector<T>::iterator q = QTable.MCoeffs.begin(); q != QTable.MCoeffs.end(); ++q) 
          {
             M = Polynomial(*a, *q);
             //cout <<"M "<< M;
             cover.reset();
             if( (M.value() > mbest.value()) && M.wellFormed() && (M.sum() < d_cubed)) //ignore M that are too small, or badly formed
             {
                for(std::vector<T>::iterator x = XTable.XCoeffs.begin(); x != XTable.XCoeffs.end(); ++x)
                {
                   X = Polynomial(*a, *x);
                   if(X.wellFormed())
                   {
                    X_prime = X-M;
                    
                    temp.at(X_prime.sum()) = X_prime;
                    cover[X_prime.sum()] = 1;	
                    //cout << X_prime << endl;
                   }
                }// end xcos loop
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
             }
          }
       }
   end = clock();
   cout<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n";
//need to write out mbest and best to a file.	
   out.open("./results.txt");
   if(out)
      {
         out << "d: " << argv[1] << endl;
         out << "modulus: " << mbest << endl;
         out << "generators: " << best[0].A << endl;
         for(int i=0; i < mbest.sum(); ++i)
         {
            out << best[i];
            out << best[i].s;
         }
         out<< "Program ran for "<< (double)(end - start)/(double)CLOCKS_PER_SEC <<" seconds. \n";
      }
   out.close();
   archive.close();
   return 0;
}
